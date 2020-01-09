set QTEXTENSIONS_VERSION=%1.%2
set QMAKE=%3
set SRC_PREFIX=%4
set INSTALL_DIR=%5


FOR /F "tokens=* USEBACKQ" %%F IN (`%QMAKE% -query QT_INSTALL_BINS`) DO (
SET QDOC=%%F
)

FOR /F "tokens=* USEBACKQ" %%F IN (`%QMAKE% -query QT_INSTALL_DOCS`) DO (
SET QT_INSTALL_DOCS=%%F
)

FOR /F "tokens=* USEBACKQ" %%F IN (`%QMAKE% -query QT_INSTALL_HEADERS`) DO (
SET QT_INSTALL_HEADERS=%%F
)

FOR /F "tokens=* USEBACKQ" %%F IN (`%QMAKE% -query QT_VERSION`) DO (
SET QT_VERSION=%%F
SET QT_VER=%%F
SET QT_VERSION_TAG=%%F
)

set QDOC=%QDOC%\qdoc

echo %QDOC%
echo %QT_INSTALL_DOCS%

SET BUILDDIR=%cd%

mkdir doc

set OUT=%cd%\doc
rmdir %OUT% /s /q
mkdir %OUT%

pushd %SRC_PREFIX%
%QDOC% --outputdir %OUT% --debug --log-progress libqtextensions.qdocconf
copy index.html %OUT%
popd

xcopy /s /y doc %INSTALL_DIR%

