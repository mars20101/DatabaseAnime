#ifndef TAGS_H
#define TAGS_H

#include <QStringListModel>
#include <QListView>
#include <QModelIndexList>
#include <QStringList>

namespace TagsHelper {

/* Selects every view item that matches a tag from the comma-separated
   `tagsText` and returns the tags absent from the list. The returned tags
   are the ones that should stay in the line edit, so that clicking an item
   in the list really adds or removes it without duplicating tags. */
inline QStringList markTagsFromText( QListView *view, QStringListModel *model, const QString &tagsText )
{
    const QStringList allTags = model->stringList();
    QStringList customTags;

    QItemSelectionModel *sel = view->selectionModel();
    const QStringList tags = tagsText.split( ',', Qt::SkipEmptyParts );
    for( const QString &rawTag : tags ){
        const QString tag = rawTag.trimmed();
        if( tag.isEmpty() )
            continue;

        const int row = ( sel ) ? allTags.indexOf( tag ) : -1;
        if( row >= 0 )
            sel->select( model->index( row ), QItemSelectionModel::Select );
        else
            customTags << tag;
    }

    return customTags;
}

/* Builds a unique comma-separated tags string from the selected list items
   and the line edit text. */
inline QString buildTagsText( QListView *view, const QString &lineEditText )
{
    QStringList tags;

    if( QItemSelectionModel *sel = view->selectionModel() ){
        const QModelIndexList selected = sel->selectedIndexes();
        for( const QModelIndex &index : selected ){
            const QString tag = index.data( Qt::DisplayRole ).toString();
            if( ! tags.contains( tag ) )
                tags << tag;
        }
    }

    const QStringList typedTags = lineEditText.split( ',', Qt::SkipEmptyParts );
    for( const QString &rawTag : typedTags ){
        const QString tag = rawTag.trimmed();
        if( ! tag.isEmpty() && ! tags.contains( tag ) )
            tags << tag;
    }

    return tags.join( ", " );
}

} // namespace TagsHelper

#endif // TAGS_H
