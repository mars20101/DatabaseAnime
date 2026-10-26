![Logo](./DatabaseAnime/images/DBA_logo_m.png)

# Database Anime [ [Rus](./README.md) | Eng ]

> **This is a fork of the original project.**
> Original: [LibertaSoft/DatabaseAnime](https://github.com/LibertaSoft/DatabaseAnime),
> author: [Demetri0](https://github.com/Demetri0) (published under the **LibertaSoft** name).
> The last commit of the original repository is November 21, 2021; upstream development has stopped.
> Fork repository: <https://github.com/mars20101/DatabaseAnime>
> The original READMEs are kept for history: [README_orig.md](./README_orig.md) · [README_orig_eng.md](./README_orig_eng.md).

### What this program is

**DatabaseAnime** is an application to systematize anime, manga, AMV and dorama: what you have
already watched, what you still want to watch, and what you have just heard about. The database
is stored in SQLite, some data is fetched through the [shikimori.io](https://shikimori.io) API.

### Why this fork

The original builds against Qt 5. My system has Qt 6, and the program just had to be made to keep
working. The fork does exactly one big thing — it ports the project to Qt 6 without a Qt 5
compatibility shim. It has no other goals.

### What has changed in the fork

- The project has been ported to Qt 6: Qt 5 is no longer supported and there is no compatibility shim.
- The tags panel in the edit dialogs was updated: tags already saved in a record are marked in the
  genre list, so they can be added and removed with a click.
- Small interface fixes for Qt 6 and the Breeze style: the record information panel no longer clips
  long genres and descriptions, and the settings dialog and the panel splitter look as they should.
- The Shikimori address was updated to the current domain (`shikimori.io`).

Details are in [CHANGELOG.md](./CHANGELOG.md).

### Status: maintained for personal needs

- This is a version ported for my own needs. It works for me — that is enough.
- No new features are planned, third-party changes are not reviewed, fix deadlines are not guaranteed.
- The program is provided **"as is"**, without any warranties, including no warranty of working
  fitness or fitness for any particular purpose. You are responsible for the safety of your database.
- Verified on Linux (KDE, Breeze style) with Qt 6.11.2. Not built or tested on Windows and macOS.
- The [AUR](https://aur.archlinux.org/packages/databaseanime-git/) package belongs to the original Qt5
  version: this fork does not update or support it.
- Bugs and requests for the original project go upstream:
  [issues](https://github.com/LibertaSoft/DatabaseAnime/issues).

### Dependencies

- Qt >= 6.0: modules `core`, `gui`, `widgets`, `sql`, `xml`, `network`
  (built and tested with Qt 6.11.2)
- A C++17 compiler
- SQLite >= 3.7

### Building from source

```bash
mkdir build && cd build
qmake6 ../DBA_Workspace.pro      # the application (same as ../DatabaseAnime/DatabaseAnime.pro)
make
```

Unit tests are a separate project: `qmake6 ../DatabaseAnime/Unit-Tests/Unit-Tests.pro && make`.

Translations are not included in the repository (`*.qm` is in `.gitignore`). To build locales:

```bash
lrelease6 ../DatabaseAnime/DatabaseAnime_ru.ts ../DatabaseAnime/DatabaseAnime_en.ts
```

The `*.qm` files appear next to the `.ts` files. Put them into the `l10n` directory inside the
program's data directory:

```bash
mkdir -p ~/.local/share/LibertaSoft/DatabaseAnime/l10n
mv ../DatabaseAnime/*.qm ~/.local/share/LibertaSoft/DatabaseAnime/l10n/
```

The application looks for `l10n/DatabaseAnime_<lang>.qm` in the data directories:
`~/.local/share/LibertaSoft/DatabaseAnime/l10n`, plus the system-wide
`/usr/local/share/LibertaSoft/DatabaseAnime/l10n` and `/usr/share/LibertaSoft/DatabaseAnime/l10n`.

### Installing from packages

The repository contains a [`packaging/`](./packaging/) directory with recipes for Linux
distributions; detailed instructions are in [packaging/README_eng.md](./packaging/README_eng.md):

- **Arch Linux**: `packaging/arch/databaseanime` (stable release) and
  `packaging/arch/databaseanime-git` (live `master` branch). The PKGBUILDs are meant for local
  builds with `makepkg`.
- **Gentoo**: a small overlay, connected either from the dedicated branch
  [`gentoo-overlay`](https://github.com/mars20101/DatabaseAnime/tree/gentoo-overlay) (the overlay
  content sits at the root of that branch) or straight from `packaging/gentoo`.

These packages are unofficial, made by the fork author and, like everything else here, "as is".

### Where the program stores its data

On Linux: `~/.local/share/LibertaSoft/DatabaseAnime` (the `DatabaseAnime.sqlite` database, covers,
styles, translations) and `~/.config/LibertaSoft/DatabaseAnime.conf` (settings). In a Qt5 build Qt
added an extra `data/` directory — `~/.local/share/data/LibertaSoft/DatabaseAnime` — so when moving
from the original Qt5 version you may have to copy the old files manually.

### License

- [GNU GPLv3](./LICENSE)
- The copyright of the original code belongs to the author of the original project. This fork is
  not affiliated with LibertaSoft and is not an "official continuation" of the project.
- The name "DatabaseAnime", the icon and the logo are materials of the original project, their
  rights remain with their author.

### Acknowledgments

- To the author of the original project — for the program itself. The full list of the original's
  acknowledgments (idea, design, logo, testing) is in [README_orig.md](./README_orig.md).
- To the [shikimori.io](https://shikimori.io) portal — for providing the API.

### Historical documents of the original

- [ToDo.md](./DatabaseAnime/ToDo.md) and [ChangeLog.md](./DatabaseAnime/ChangeLog.md) in the
  `DatabaseAnime/` directory are historical notes of the original author; the fork lives by
  [CHANGELOG.md](./CHANGELOG.md) in the root.
