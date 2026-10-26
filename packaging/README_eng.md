# Packaging recipes [ [Rus](./README.md) | Eng ]

Build recipes for installing DatabaseAnime on different Linux distributions.

```
packaging/
├── arch/
│   ├── databaseanime/     PKGBUILD for the tagged release + .desktop file
│   └── databaseanime-git/ PKGBUILD tracking the master branch + .desktop file
└── gentoo/                Gentoo mini-overlay
    ├── profiles/repo_name
    └── app-misc/databaseanime/
        ├── databaseanime-1.5.0.ebuild   release ebuild (GitHub tarball)
        ├── databaseanime-9999.ebuild    live ebuild (git master)
        └── metadata.xml
```

Both variants build the project out of source with qmake, compile the
translation files with `lrelease` into `l10n/*.qm`, and install:

- `/usr/bin/dba` — the binary
- `/usr/share/LibertaSoft/DatabaseAnime/l10n/*.qm` — translations
- `/usr/share/icons/hicolor/*/apps/databaseanime.png` — icons (64x64, 256x256, 512x512)
- `/usr/share/applications/DatabaseAnime.desktop` — menu entry (Arch ships the
  `.desktop` file from this directory; Gentoo generates it with
  `make_desktop_entry`)

Build requirements: Qt6 (Core, Gui, Widgets, Sql with the SQLite driver, XML,
Network with SSL/TLS support) and OpenSSL. The app talks to Shikimori over
HTTPS only, so TLS support in Qt Network is mandatory; SQLite is the only
database engine used at runtime.

## Arch Linux

Build and install locally:

```sh
cd packaging/arch/databaseanime      # or databaseanime-git
makepkg -si
```

## Gentoo

`packaging/gentoo/` is a self-contained mini-overlay. Two ways to use it:

### A. Local overlay (direct subfolder configuration)

Clone the repository into your local source directory. A sparse checkout keeps the
download minimal by fetching only the overlay directory:

```sh
git clone --filter=blob:none --sparse \
    https://github.com/mars20101/DatabaseAnime \
    /var/db/repos/databaseanime-src
cd /var/db/repos/databaseanime-src
git sparse-checkout set packaging/gentoo
```

Register the overlay in `/etc/portage/repos.conf/databaseanime.conf`. Note that
`location` points directly to the subfolder, and automatic sync is disabled to
prevent Portage from looking for a `.git` folder in the subfolder root:

```ini
[databaseanime]
location = /var/db/repos/databaseanime-src/packaging/gentoo
auto-sync = no
```

Install the package. You can choose to build the latest tagged release (default)
or the live `master` branch:

```sh
# Option 1: Install the latest tagged release
echo "app-misc/databaseanime ~amd64" > /etc/portage/package.accept_keywords/databaseanime
emerge -av app-misc/databaseanime

# Option 2: Install the live version from the master branch
# echo "app-misc/databaseanime **" > /etc/portage/package.accept_keywords/databaseanime
# emerge -av app-misc/databaseanime
```

To update the overlay later, manually pull the changes inside the repository root:

```sh
cd /var/db/repos/databaseanime-src
git pull
```

### B. Automatic sync via Portage (Recommended)

The Gentoo overlay is provided via the `gentoo-overlay` branch of this repository.
You can configure Portage to automatically fetch and update it alongside your main system tree.

Create a repository configuration file at `/etc/portage/repos.conf/databaseanime.conf`:

```ini
[databaseanime]
location = /var/db/repos/databaseanime
sync-type = git
sync-uri = https://github.com/mars20101/DatabaseAnime.git
sync-git-clone-extra-opts = -b gentoo-overlay
auto-sync = yes
```

Sync the overlay to initialize the local clone:

```sh
emaint sync -r databaseanime
```

Install the package. You can choose to build the latest tagged release (default) or
the live `master` branch:

```sh
# Option 1: Install the latest tagged release
echo "app-misc/databaseanime ~amd64" > /etc/portage/package.accept_keywords/databaseanime
emerge -av app-misc/databaseanime

# Option 2: Install the live version from the master branch
# echo "app-misc/databaseanime **" > /etc/portage/package.accept_keywords/databaseanime
# emerge -av app-misc/databaseanime
```

