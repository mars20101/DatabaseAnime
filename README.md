![Logo](./DatabaseAnime/images/DBA_logo_m.png)

# Database Anime [ Rus | [Eng](./README_eng.md) ]

> **Это форк оригинального проекта.**
> Оригинал: [LibertaSoft/DatabaseAnime](https://github.com/LibertaSoft/DatabaseAnime),
> автор — [Demetri0](https://github.com/Demetri0) (публикуется под именем **LibertaSoft**).
> Последний коммит оригинального репозитория — 21 ноября 2021 года, разработка оригинала прекращена.
> Репозиторий форка: <https://github.com/mars20101/DatabaseAnime>
> Оригинальные README сохранены для истории: [README_orig.md](./README_orig.md) · [README_orig_eng.md](./README_orig_eng.md).

### Что это за программа

**DatabaseAnime** — программа для систематизации аниме, манги, AMV и дорамы: того, что вы уже
смотрели, что ещё хотите посмотреть и о чём просто слышали. База хранится в SQLite, часть
данных подтягивается через API [shikimori.io](https://shikimori.io).

### Зачем этот форк

Оригинал собирается под Qt 5. В моей системе Qt 6, и программу нужно было просто заставить
работать дальше. Форк делает ровно одну большую вещь — переносит проект на Qt 6 без прослойки
совместимости с Qt 5. Других целей у форка нет.

### Что изменено в форке

- Проект перенесён на Qt 6: Qt 5 больше не поддерживается, прослойки совместимости нет.
- Обновлена панель тегов в диалогах редактирования: теги, уже сохранённые в записи, отмечаются
  в списке жанров, поэтому их можно добавлять и убирать кликом.
- Мелкие исправления интерфейса под Qt 6 и стиль Breeze: панель информации о записи перестала
  обрезать длинные жанры и описание, диалог настроек и разделитель панелей выглядят как надо.
- Адрес Shikimori обновлён на актуальный домен (`shikimori.io`).

Подробности — в [CHANGELOG.md](./CHANGELOG.md).

### Статус: поддерживается для личных нужд

- Это версия, портированная под мои собственные нужды. Она работает у меня — этого достаточно.
- Новых функций не планируется, чужие изменения не ревьюятся, сроки исправлений не гарантируются.
- Программа предоставляется **«как есть» (as is)**, без каких-либо гарантий, в том числе без
  гарантии работоспособности или пригодности для какой-либо цели. Ответственность за сохранность
  вашей базы данных лежит на вас.
- Проверено на Linux (KDE, стиль Breeze) с Qt 6.11.2. Под Windows и macOS не собиралось и не
  тестировалось.
- Пакет в [AUR](https://aur.archlinux.org/packages/databaseanime-git/) относится к оригинальной
  Qt5-версии: этот форк его не обновляет и не поддерживает.
- Баги и пожелания к оригинальному проекту — в upstream:
  [issues](https://github.com/LibertaSoft/DatabaseAnime/issues).

### Зависимости

- Qt >= 6.0: модули `core`, `gui`, `widgets`, `sql`, `xml`, `network`
  (собрано и протестировано с Qt 6.11.2)
- Компилятор с C++17
- SQLite >= 3.7

### Сборка из исходников

```bash
mkdir build && cd build
qmake6 ../DBA_Workspace.pro      # приложение (то же, что ../DatabaseAnime/DatabaseAnime.pro)
make
```

Модульные тесты — отдельный проект: `qmake6 ../DatabaseAnime/Unit-Tests/Unit-Tests.pro && make`.

Переводы в репозиторий не включены (`*.qm` в `.gitignore`). Чтобы собрать локаль:

```bash
lrelease6 ../DatabaseAnime/DatabaseAnime_ru.ts ../DatabaseAnime/DatabaseAnime_en.ts
```

Файлы `*.qm` появятся рядом с `.ts`. Сложить их нужно в каталог `l10n` каталога данных программы:

```bash
mkdir -p ~/.local/share/LibertaSoft/DatabaseAnime/l10n
mv ../DatabaseAnime/*.qm ~/.local/share/LibertaSoft/DatabaseAnime/l10n/
```

Приложение ищет `l10n/DatabaseAnime_<lang>.qm` в каталогах данных: `~/.local/share/LibertaSoft/DatabaseAnime/l10n`,
а также системных `/usr/local/share/LibertaSoft/DatabaseAnime/l10n` и `/usr/share/LibertaSoft/DatabaseAnime/l10n`.

### Установка из пакетов

В репозитории есть каталог [`packaging/`](./packaging/) с рецептами для Linux-дистрибутивов;
подробные инструкции — в [packaging/README.md](./packaging/README.md):

- **Arch Linux**: `packaging/arch/databaseanime` (стабильный релиз) и
  `packaging/arch/databaseanime-git` (живая ветка `master`). PKGBUILD рассчитаны на локальную
  сборку через `makepkg`.
- **Gentoo**: мини-оверлей, подключается из отдельной ветки
  [`gentoo-overlay`](https://github.com/mars20101/DatabaseAnime/tree/gentoo-overlay) (содержимое
  оверлея лежит в корне той ветки) или прямо из `packaging/gentoo`.

Пакеты неофициальные, делаются форк-автором и, как всё здесь, — «как есть».

### Где программа хранит данные

На Linux: `~/.local/share/LibertaSoft/DatabaseAnime` (база `DatabaseAnime.sqlite`, обложки,
стили, переводы) и `~/.config/LibertaSoft/DatabaseAnime.conf` (настройки). В Qt5-сборке Qt
добавлял лишний каталог `data/` — `~/.local/share/data/LibertaSoft/DatabaseAnime`, поэтому при
переходе с оригинальной Qt5-версии старые файлы, возможно, придётся перенести вручную.

### Лицензия

- [GNU GPLv3](./LICENSE)
- Авторские права на код оригинала принадлежат автору оригинального проекта. Этот форк не
  аффилирован с LibertaSoft и не является «официальным продолжением» проекта.
- Название «DatabaseAnime», иконка и логотип — материалы оригинального проекта, права на них
  остаются у их автора.

### Благодарности

- Автору оригинального проекта — за саму программу. Полный список благодарностей оригинала
  (идея, дизайн, логотип, тесты) — в [README_orig.md](./README_orig.md).
- Порталу [shikimori.io](https://shikimori.io) — за предоставленный API.

### Исторические документы оригинала

- [ToDo.md](./DatabaseAnime/ToDo.md) и [ChangeLog.md](./DatabaseAnime/ChangeLog.md) в каталоге
  `DatabaseAnime/` — исторические заметки оригинального автора; форк живёт по
  [CHANGELOG.md](./CHANGELOG.md) в корне.
