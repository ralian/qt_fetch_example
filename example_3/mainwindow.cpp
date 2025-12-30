#include "mainwindow.h"

#include <QApplication>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QInputDialog>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMimeData>
#include <QStatusBar>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextStream>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Qt6 Simple Text Editor"));

    m_textEdit = new QTextEdit(this);
    setCentralWidget(m_textEdit);

    setAcceptDrops(true);
    m_textEdit->setAcceptDrops(false); // Disable on text edit, handle at window level

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile);
    openAction->setShortcuts(QKeySequence::Open);
    
    QAction *saveAction = fileMenu->addAction(tr("&Save"), this, &MainWindow::saveFile);
    saveAction->setShortcuts(QKeySequence::Save);
    
    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction(tr("E&xit"), qApp, &QApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *findMenu = menuBar()->addMenu(tr("&Edit"));
    QAction *findAction =
        findMenu->addAction(tr("&Find..."), this, &MainWindow::find);
    findAction->setShortcuts(QKeySequence::Find);
    m_findNextAction = findMenu->addAction(tr("Find &Next"), this, &MainWindow::findNext);
    m_findNextAction->setShortcuts(QKeySequence::FindNext);
    m_findPreviousAction = findMenu->addAction(tr("Find &Previous"), this,
                                               &MainWindow::findPrevious);
    m_findPreviousAction->setShortcuts(QKeySequence::FindPrevious);

    menuBar()->addMenu(tr("&About"))->addAction(tr("&About Qt"), qApp, &QApplication::aboutQt);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                     tr("All Files (*.*)"));
    if (fileName.isEmpty())
        return;

    loadFile(fileName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        statusBar()->showMessage(tr("Cannot open file: %1").arg(fileName), 3000);
        return;
    }

    QTextStream in(&file);
    m_textEdit->setPlainText(in.readAll());
    file.close();

    m_OpenFileInfo = QFileInfo(fileName);
    statusBar()->showMessage(tr("Loaded file: %1").arg(fileName), 3000);
}

void MainWindow::saveFile()
{
    if (m_OpenFileInfo.filePath().isEmpty()) {
        statusBar()->showMessage(tr("No file open to save"), 3000);
        return;
    }

    QFile file(m_OpenFileInfo.filePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        statusBar()->showMessage(tr("Cannot save file: %1").arg(m_OpenFileInfo.filePath()), 3000);
        return;
    }

    QTextStream out(&file);
    out << m_textEdit->toPlainText();
    file.close();

    statusBar()->showMessage(tr("Saved file: %1").arg(m_OpenFileInfo.filePath()), 3000);
}

void MainWindow::find()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Find"), tr("Find:"),
                                                QLineEdit::Normal, m_searchString, &ok);
    if (ok && !searchText.isEmpty()) {
        m_searchString = searchText;
        // Start search from the beginning
        QTextCursor cursor = m_textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        m_textEdit->setTextCursor(cursor);
        findNext();
    }
}

void MainWindow::findNext()
{
    if (m_searchString.isEmpty()) {
        find();
        return;
    }

    if (m_textEdit->find(m_searchString)) {
        statusBar()->showMessage(tr("Found: %1").arg(m_searchString), 2000);
    } else {
        // Wrap around to the beginning and try again
        QTextCursor cursor = m_textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        m_textEdit->setTextCursor(cursor);
        if (m_textEdit->find(m_searchString)) {
            statusBar()->showMessage(tr("Found: %1 (wrapped)").arg(m_searchString), 2000);
        } else {
            statusBar()->showMessage(tr("Not found: %1").arg(m_searchString), 3000);
        }
    }
}

void MainWindow::findPrevious()
{
    if (m_searchString.isEmpty()) {
        find();
        return;
    }

    if (m_textEdit->find(m_searchString, QTextDocument::FindBackward)) {
        statusBar()->showMessage(tr("Found: %1").arg(m_searchString), 2000);
    } else {
        // Wrap around to the end and try again
        QTextCursor cursor = m_textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        m_textEdit->setTextCursor(cursor);
        if (m_textEdit->find(m_searchString, QTextDocument::FindBackward)) {
            statusBar()->showMessage(tr("Found: %1 (wrapped)").arg(m_searchString), 2000);
        } else {
            statusBar()->showMessage(tr("Not found: %1").arg(m_searchString), 3000);
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        // Take the first file if multiple are dropped
        if (!urlList.isEmpty()) {
            QString fileName = urlList.first().toLocalFile();
            if (!fileName.isEmpty()) {
                loadFile(fileName);
                event->acceptProposedAction();
            }
        }
    }
}
