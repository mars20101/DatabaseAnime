#ifndef SCROLLCONTENT_H
#define SCROLLCONTENT_H

#include <QEvent>
#include <QObject>
#include <QScrollArea>
#include <QLayout>
#include <QMargins>
#include <QLabel>
#include <QSizePolicy>
#include <QWidget>

/* Sizes the widget of a QScrollArea by hand instead of relying on
   QScrollArea::setWidgetResizable(). When the viewport of a resizable
   scroll area is shrunk, Qt can resize the content widget without ever
   activating its layout at the new width, so word-wrapped labels keep
   the heights computed for the old (wider) width and get clipped. Here
   the content widget is resized to the viewport width (or to the layout
   minimum if that is wider), the layout is activated at that width, and
   the content height is then taken from the real geometries the layout
   assigned to the items, so every row is as tall as it needs to be and
   nothing is cut off. Word-wrapped labels are also switched to an
   expanding horizontal policy, otherwise QFormLayout keeps their column
   at the width of the longest word no matter how much room there is. */
class ScrollContentSizer : public QObject
{
public:
    explicit ScrollContentSizer( QScrollArea *area )
        : QObject( area ),
          _Area( area )
    {
        _Area->setWidgetResizable( false );
        _Area->viewport()->installEventFilter( this );
    }

    void sizeContent()
    {
        QWidget *content = _Area->widget();
        QLayout *lay = ( content ) ? content->layout() : nullptr;
        if( ! content || ! lay )
            return;

        for( QObject *child : content->children() ){
            QLabel *label = qobject_cast<QLabel*>( child );
            if( label && label->wordWrap()
                    && label->sizePolicy().horizontalPolicy() != QSizePolicy::Expanding )
                label->setSizePolicy( QSizePolicy::Expanding,
                                      label->sizePolicy().verticalPolicy() );
        }

        // The layout's own minimumSize() is not reliable here (it can report
        // the full hint width), so derive the real minimum from the widgets:
        // the longest unbreakable word plus the widest caption line.
        int widestWord = 0;
        int widestCaption = 0;
        for( QObject *child : content->children() ){
            QLabel *label = qobject_cast<QLabel*>( child );
            if( ! label )
                continue;
            if( label->wordWrap() )
                widestWord = qMax( widestWord, label->minimumSizeHint().width() );
            else
                widestCaption = qMax( widestCaption, label->minimumSizeHint().width() );
        }
        const QMargins margins = lay->contentsMargins();
        const int minW = margins.left() + margins.right()
                       + lay->spacing() + widestWord + widestCaption;

        // The layout's size constraint pushes its minimum onto the content
        // widget, so QWidget::resize() gets clamped back to the hint width.
        // Without a constraint the content widget can really be sized to the
        // viewport, and the layout shrinks its columns within that width.
        lay->setSizeConstraint( QLayout::SetNoConstraint );
        content->setMinimumSize( 0, 0 );

        const int viewW = _Area->viewport()->width();
        const int viewH = _Area->viewport()->height();

        content->resize( qMax( viewW, minW ), viewH );
        lay->activate();

        // QFormLayout only consults heightForWidth() when the whole layout
        // reports hasHeightForWidth(); otherwise rows keep the heights that
        // were computed for the hint widths and labels placed in narrower
        // columns get clipped vertically. Enforce the needed height per
        // word-wrapped label at the width it actually got.
        for( QObject *child : content->children() ){
            QLabel *label = qobject_cast<QLabel*>( child );
            if( ! label || ! label->wordWrap() )
                continue;
            label->setMinimumHeight( label->heightForWidth( label->width() ) );
        }
        lay->activate();

        // Read the heights the layout actually assigned and grow the content
        // widget to fit them all, so the scroll area can reach the rest.
        int needed = lay->contentsMargins().bottom();
        for( QObject *child : content->children() ){
            if( QWidget *childWidget = qobject_cast<QWidget*>( child ) )
                needed = qMax( needed, childWidget->geometry().bottom() + 1 );
        }
        content->resize( content->width(), qMax( viewH, needed ) );
        content->show();
    }

    bool eventFilter( QObject *obj, QEvent *event ) override
    {
        if( obj == _Area->viewport()
                && ( event->type() == QEvent::Resize
                     || event->type() == QEvent::Show ) )
            sizeContent();

        return false;
    }

private:
    QScrollArea *_Area;
};

#endif // SCROLLCONTENT_H
