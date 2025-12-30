#pragma once

#include <QAction>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileInfo>
#include <QMainWindow>
#include <QString>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void openFile();
    void saveFile();
    void find();
    void findNext();
    void findPrevious();

private:
    void loadFile(const QString &fileName);

    QTextEdit *m_textEdit{ nullptr };
    QFileInfo m_OpenFileInfo;
    QAction *m_findNextAction{ nullptr };
    QAction *m_findPreviousAction{ nullptr };
    QString m_searchString;
    // QFile *m_file{ nullptr };
};
