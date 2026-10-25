#ifndef ELIDEDLISTDELEGATE_H
#define ELIDEDLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QStyle>
#include <QPainter>
#include <QApplication>
#include <QModelIndex>

/* Draws list items so that a truncated title ("…") starts at the same left
   indent as the titles that fit into the column.

   The Breeze style insets the item text rect by an amount that depends on the
   free space around the text (see SE_ItemViewItemText in its subElementRect):
   text that does not fit gets no inset at all, so an elided title is drawn a
   few pixels left of the fully drawn ones. Pre-eliding the title to the width
   that already includes the full inset makes the style take its "text fits"
   path and draw every row at the same indent. Styles without such behaviour
   (Fusion and others) return the same rect for both probes and are left
   untouched. */
class ElidedListDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        const QWidget *w = opt.widget;
        QStyle *style = w ? w->style() : qApp->style();

        if (!opt.text.isEmpty() && (opt.features & QStyleOptionViewItem::HasDisplay)) {
            // Compare the text rects of an empty and of an overlong title to
            // find the horizontal inset the style adds only when text can spare it.
            QStyleOptionViewItem probe(opt);
            probe.text.clear();
            const QRect full = style->subElementRect(QStyle::SE_ItemViewItemText, &probe, w);
            probe.text = QString(1024, QChar(u'и'));
            const QRect base = style->subElementRect(QStyle::SE_ItemViewItemText, &probe, w);

            const int inset = (full.left() - base.left()) + (base.right() - full.right());
            if (inset > 0) {
                const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, &opt, w) + 1;
                const int maxText = full.width() - 2 * textMargin;
                if (opt.fontMetrics.horizontalAdvance(opt.text) > maxText)
                    opt.text = opt.fontMetrics.elidedText(opt.text, Qt::ElideRight, maxText);
            }
        }

        // Not QStyledItemDelegate::paint(): it runs initStyleOption() again and
        // would re-read the full title from the model, undoing the pre-elision.
        style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, w);
    }
};

#endif // ELIDEDLISTDELEGATE_H
