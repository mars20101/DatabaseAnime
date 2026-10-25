# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.5.0] - 2026-10-25
- Ported the project to Qt6 (built and tested with Qt 6.11): removed Qt5-only APIs
  (`QRegExp`, `QDirModel`, `QString::null`, `QStandardPaths::DataLocation`, `QSet::toList`,
  `foreach`, `QPalette::ButtonText`, `QHBoxLayout::setMargin`, old `enterEvent` signature)
  instead of using Qt5Compat
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
- Fixed settings dialog fields being squeezed down to their size hint under Qt 6: the color
  swatches turned into small squares and combos or the search-limit slider row stopped
  spanning their group box once the window is wide. Qt 6 changed QFormLayout's default
  fieldGrowthPolicy (SH_FormLayoutFieldGrowthPolicy) from AllNonFixedFieldsGrow to
  MinimumFieldSizePolicy, which keeps fields living in a nested layout (the color pickers, the
  slider+spinbox row) and non-expanding widgets at their sizeHint() instead of stretching them
  across the field column; every QFormLayout of the dialog now gets
  setFieldGrowthPolicy(AllNonFixedFieldsGrow), restoring the Qt 5 default in the same loop that
  already fixes label alignment
- Updated the default Shikimori address to `https://shikimori.io`: `shikimori.org` no longer
  answers, while the API keeps the very same paths on `.io`. The default in
  `ShikimoriApi::getShikimoriUrl()`, the doc comments and the "Search on shikimori.io"
  tooltips of the add-anime and add-manga dialogs, together with the ru/en translation
  catalogs, now point to the new domain
- Removed the `vk.com` button from the welcome page (the upstream VK group has nothing to do
  with this fork) and pointed the `GitHub` button and the update check at the fork
  repository; the update check now ignores an empty reply, which is what GitHub answers for
  a repository without any releases
- Rewrote `README.md` and `README_eng.md` for this fork and kept the upstream READMEs
  verbatim as `README_orig.md` and `README_orig_eng.md`, adjusting only the link between
  the two archived pages
- Removed the "Use HTTPS" checkbox and the `USE_SSL` setting, porting the cleanup the
  upstream author had started on his never-merged `develop` branch in 2019: Shikimori only
  answers over HTTPS now, so requests always use the `https://` scheme and the only network
  option left is the "Shikimori API URL" field, which falls back to `https://shikimori.io`
  both when saved empty and when read by `ShikimoriApi::getShikimoriUrl()`; a `lupdate`
  pass dropped the dead "Use HTTPS" catalog entries and refreshed stale source locations
- Fixed elided anime-list titles ("…") starting left of the titles that fit the column:
  breeze-qt6 insets its `SE_ItemViewItemText` subelement rect by however much free space
  the text spares, so a title that does not fit gets a zero inset and is drawn at the
  unpadded position while fitting rows keep the full padding; the new `ElidedListDelegate`
  installed on the list view probes the style for that length-dependent inset (comparing
  the text rects of an empty and of an overlong title) and pre-elides the title to the
  padded width, which makes Breeze take its "text fits" path and draw every row at the
  same indent; styles whose text rect does not depend on the text length (Fusion and
  others) return identical probe rects and are drawn exactly as before
