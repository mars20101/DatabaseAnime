# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
- Ported the project to Qt6 (built and tested with Qt 6.11): removed Qt5-only APIs
  (`QRegExp`, `QDirModel`, `QString::null`, `QStandardPaths::DataLocation`, `QSet::toList`,
  `foreach`, `QPalette::ButtonText`, `QHBoxLayout::setMargin`, old `enterEvent` signature)
  instead of using Qt5Compat
- Added new settings for change Shikimori API URL
- Fixed tags panel in edit dialogs (anime, manga, dorama, AMV): tags saved in a record are now
  marked in the genre list when opening for editing, so they can be added/removed by clicking,
  and saving no longer duplicates tags present both in the list selection and the text field
- Fixed record information panel (anime, manga, dorama, AMV): properties are now placed in a
  widget inside the scroll area (`setWidget`/`setWidgetResizable`) instead of laying out the
  scroll area viewport directly, so long wrapped texts (genres, studio, alt title, description)
  no longer get squeezed and overlap when the panel is shorter than the content
- Fixed vertical clipping of wrapped genres/description in the record information panel: the
  content widget is now sized manually via `ScrollContentSizer` (viewport width plus enforced
  `heightForWidth()` of every wrapped label), because `QFormLayout` stops consulting
  `heightForWidth()` once wrapped labels expand, so rows kept heights computed for hint widths
  and cut off text at narrower window sizes; the content also never exceeds the viewport width,
  so no horizontal scrollbar appears, and the vertical scrollbar reaches the full description
- Fixed captions ("Ganres:", "Alt title:", etc.) drifting away from the vertical center of
  their values in the record information panel: each word-wrapped value label is pinned to
  exactly the height its text needs, and the caption of the same row is made equally tall,
  so both texts share one vertical center line at any window size
- Fixed settings dialog leaving wide empty bands above and below its regions when the window
  is enlarged: the category list had a `Maximum` vertical size policy, and `QSplitter` caps
  its own maximum height by the children's maximums, so the whole splitter stayed pinned to
  the size hints and could not grow with the window; the list now has a `Preferred` vertical
  policy, so the category list and the settings area stretch to the full window height while
  the list keeps its fixed maximum width and the page layouts stay untouched
- Regenerated translation sources (`DatabaseAnime_ru.ts`, `DatabaseAnime_en.ts`) with Qt 6
  `lupdate`: the catalogs had been fully `vanished` since the pre-Qt6 project reorganization,
  and the update revived 375 finished translations (ru) that `lrelease` had produced nothing
  for; 29 new strings (settings color-role labels, shortcut captions, Shikimori URL options,
  progress-bar switches) remain untranslated, and dead strings are kept as `vanished`
- Fixed splitter handle in the main window showing as a wide bright bar under Breeze for Qt6:
  breeze-qt6 fills the whole handle with the palette separator color (`CE_Splitter` →
  `drawSplitterControl`), while breeze-qt5 did not implement `CE_Splitter` at all and left an
  invisible gap; the main-window splitter now overrides handle painting via a widget-level
  stylesheet (`QSplitter::handle { border: none; background: palette(window); }`), restoring the
  old invisible look; the handle width and dragging behavior are unchanged
- Fixed settings dialog group box headers ("Anime:", "Global:", etc.) showing horizontally
  centered *inside* their frames under Breeze for Qt6: breeze-qt6 rewrote
  `drawGroupBoxComplexControl` after `QCommonStyle` and hardcodes `Qt::AlignHCenter` for the
  title, while breeze-qt5 delegated title drawing to `QCommonStyle` (left-aligned) and shifted
  the frame below it; the dialog now sets a dialog-level stylesheet that moves the title
  subcontrol into the top-left margin (`subcontrol-origin: margin`,
  `subcontrol-position: top left`), so headers sit left-aligned above the frame again, while
  the frame itself is still painted by Breeze and keeps its native separator color and
  rounded corners
- Fixed labels without a field ("Genre (anime):", "User tags", ...) being indented away from
  the left edge of their group in the settings dialog, while the fields in the rows above
  started at that edge: `QFormLayout` right-aligns its label column by default
  (`SH_FormLayoutLabelAlignment`), which is only noticeable in rows that have no field, so
  every `QFormLayout` of the dialog now gets `setLabelAlignment(Qt::AlignLeft)`; label
  alignment cannot be set through Qt Style Sheets (`QFormLayout:labelfield` is ignored by Qt),
  hence the code, and the field column keeps its width and positions
