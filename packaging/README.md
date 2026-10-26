# Рецепты сборки пакетов [ Rus | [Eng](./README_eng.md) ]

Рецепты сборки для установки DatabaseAnime в разных дистрибутивах Linux.

```
packaging/
├── arch/
│   ├── databaseanime/     PKGBUILD для тегированного релиза + .desktop-файл
│   └── databaseanime-git/ PKGBUILD, отслеживающий ветку master + .desktop-файл
└── gentoo/                Мини-оверлей Gentoo
    ├── profiles/repo_name
    └── app-misc/databaseanime/
        ├── databaseanime-1.5.0.ebuild   ebuild релиза (тарбол с GitHub)
        ├── databaseanime-9999.ebuild    live-ebuild (git master)
        └── metadata.xml
```

Оба варианта собирают проект из исходников вне дерева исходников (out of source)
с помощью qmake, компилируют файлы переводов `lrelease` в `l10n/*.qm` и устанавливают:

- `/usr/bin/dba` — бинарный файл
- `/usr/share/LibertaSoft/DatabaseAnime/l10n/*.qm` — переводы
- `/usr/share/icons/hicolor/*/apps/databaseanime.png` — иконки (64x64, 256x256, 512x512)
- `/usr/share/applications/DatabaseAnime.desktop` — пункт меню (в Arch
  `.desktop`-файл идёт в комплекте с рецептом; в Gentoo он генерируется
  через `make_desktop_entry`)

Требования для сборки: Qt6 (Core, Gui, Widgets, Sql с драйвером SQLite, XML,
Network с поддержкой SSL/TLS) и OpenSSL. Приложение общается с Shikimori только
по HTTPS, поэтому поддержка TLS в Qt Network обязательна; SQLite — единственный
используемый движок базы данных во время работы.

## Arch Linux

Сборка и установка локально:

```sh
cd packaging/arch/databaseanime      # или databaseanime-git
makepkg -si
```

## Gentoo

`packaging/gentoo/` — самодостаточный мини-оверлей. Два способа использования:

### A. Локальный оверлей (прямая настройка подпапки)

Склонируйте репозиторий в локальную директорию с исходниками. Sparse-checkout
сокращает загрузку, скачивая только директорию оверлея:

```sh
git clone --filter=blob:none --sparse \
    https://github.com/mars20101/DatabaseAnime \
    /var/db/repos/databaseanime-src
cd /var/db/repos/databaseanime-src
git sparse-checkout set packaging/gentoo
```

Зарегистрируйте оверлей в `/etc/portage/repos.conf/databaseanime.conf`. Обратите
внимание, что `location` указывает прямо на подпапку, и автоматическая
синхронизация отключена, чтобы Portage не искал папку `.git` в корне оверлея:

```ini
[databaseanime]
location = /var/db/repos/databaseanime-src/packaging/gentoo
auto-sync = no
```

Установите пакет. Можно собрать последний тегированный релиз (по умолчанию) или
live-версию из ветки `master`:

```sh
# Вариант 1: установка последнего тегированного релиза
echo "app-misc/databaseanime ~amd64" > /etc/portage/package.accept_keywords/databaseanime
emerge -av app-misc/databaseanime

# Вариант 2: установка live-версии из ветки master
# echo "app-misc/databaseanime **" > /etc/portage/package.accept_keywords/databaseanime
# emerge -av app-misc/databaseanime
```

Для последующего обновления оверлея вручную подтяните изменения в корне репозитория:

```sh
cd /var/db/repos/databaseanime-src
git pull
```

### B. Автоматическая синхронизация через Portage (рекомендуется)

Оверлей Gentoo предоставлен в ветке `gentoo-overlay` этого репозитория. Portage
можно настроить на автоматическую загрузку и обновление оверлея вместе с основным
деревом системы.

Создайте файл конфигурации репозитория `/etc/portage/repos.conf/databaseanime.conf`:

```ini
[databaseanime]
location = /var/db/repos/databaseanime
sync-type = git
sync-uri = https://github.com/mars20101/DatabaseAnime.git
sync-git-clone-extra-opts = -b gentoo-overlay
auto-sync = yes
```

Синхронизируйте оверлей, чтобы создать локальный клон:

```sh
emaint sync -r databaseanime
```

Установите пакет. Можно собрать последний тегированный релиз (по умолчанию) или
live-версию из ветки `master`:

```sh
# Вариант 1: установка последнего тегированного релиза
echo "app-misc/databaseanime ~amd64" > /etc/portage/package.accept_keywords/databaseanime
emerge -av app-misc/databaseanime

# Вариант 2: установка live-версии из ветки master
# echo "app-misc/databaseanime **" > /etc/portage/package.accept_keywords/databaseanime
# emerge -av app-misc/databaseanime
```
