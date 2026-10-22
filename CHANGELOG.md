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
