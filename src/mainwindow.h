#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "extfiledialog.h"
#include <QItemSelection>
#include <QLabel>
#include <memory>

namespace Ui {
class MainWindow;
}

namespace Scripting {
class CppConductor;
}

class SqlSyntaxHighlighter;
class QueryWidget;
class TableModel;
class FindAndReplacePanel;
class DbObjectsModel;
class DbConnection;
class DataTable;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *e);
	
private slots:
    void on_addConnectionAction_triggered();
    void on_actionAbout_triggered();
    void on_objectsView_activated(const QModelIndex &index);
    void on_objectsView_customContextMenuRequested(const QPoint &pos);
    void on_actionRefresh_triggered();
    void on_actionChange_sort_mode_triggered();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void viewModeActionTriggered(QAction *action);
    void on_actionExecute_query_triggered();
    void on_actionNew_triggered();
    void on_tabWidget_tabCloseRequested(int index);
    void sqlChanged();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void scriptSelectedObjects();
    void showContent(QModelIndex &index, const Scripting::CppConductor *content);
    void showTextualContent(const QVariant &value, const QVariant &type, std::shared_ptr<DbConnection> con);
    void objectsViewAdjustColumnWidth(const QModelIndex &);
    void on_actionFind_triggered();
    void on_tabWidget_currentChanged(int index);

private:
    QLabel _contextLabel, _positionLabel, _durationLabel;
    ExtFileDialog _fileDialog;
    QStringList _mruDirs; // QFileDialog::history() keeps unused directories :(
	Ui::MainWindow *ui;
    DbObjectsModel *_objectsModel;
    TableModel *_tableModel;
    QueryWidget* currentQueryWidget();
    QueryWidget* _objectScript;
    bool closeTab(int index);
    bool eventFilter(QObject *object, QEvent *event);
    bool ensureSaved(int index, bool ask_name = false, bool forceWarning = false);
    FindAndReplacePanel *_frPanel;
    QTimer *_hideTimer;
    QTimer *_durationRefreshTimer;
    void log(const QString &msg);
    void adjustMruDirs();

public slots:
    QVariant current(const QString &nodeType, const QString &field);
    QVariantList selected(const QString &nodeType, const QString &field);

    void refreshActions();
    void refreshContextInfo();
    void refreshCursorInfo();
    void refreshConnectionState();
    void onMessage(const QString &msg);
    void onError(const QString &err);
};

#endif // MAINWINDOW_H
