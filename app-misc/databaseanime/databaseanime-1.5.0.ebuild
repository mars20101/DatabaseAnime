EAPI=8

inherit desktop xdg

DESCRIPTION="Management of your collection Anime, Manga, AMV and Dorama"
HOMEPAGE="https://github.com/mars20101/DatabaseAnime"
SRC_URI="https://github.com/mars20101/DatabaseAnime/archive/v${PV}.tar.gz -> ${P}.tar.gz"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~amd64"

RDEPEND="
    dev-qt/qtbase:6[gui,network,sql,sqlite,widgets,xml]
"
DEPEND="
    ${RDEPEND}
"
BDEPEND="
    dev-qt/qttools:6[linguist]
"

BUILD_DIR="${WORKDIR}/${PN}-build"
S="${WORKDIR}/DatabaseAnime-${PV}"

src_configure() {
    mkdir -p "${BUILD_DIR}" || die
    cd "${BUILD_DIR}" || die
    qmake6 "${S}/DatabaseAnime/DatabaseAnime.pro" CONFIG+=release || die
}

src_compile() {
    mkdir -p "${BUILD_DIR}/l10n" || die
    local lang
    for lang in en ru; do
        lrelease6 "${S}/DatabaseAnime/DatabaseAnime_${lang}.ts" \
            -qm "${BUILD_DIR}/l10n/DatabaseAnime_${lang}.qm" || die
    done

    emake -C "${BUILD_DIR}"
}

src_install() {
    newbin "${BUILD_DIR}/DatabaseAnime" dba

    insinto /usr/share/LibertaSoft/DatabaseAnime/l10n
    doins "${BUILD_DIR}/l10n/DatabaseAnime_en.qm"
    doins "${BUILD_DIR}/l10n/DatabaseAnime_ru.qm"

    local size
    for size in 64 256 512; do
        newicon -s ${size} "DatabaseAnime/images/DBA_Icon-${size}.png" databaseanime.png
    done

    make_desktop_entry dba "Database Anime" databaseanime "Database;"
}
