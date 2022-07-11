from PyQt5.QtWidgets import QMainWindow, QApplication, QFileDialog
from PyQt5 import QtWidgets
from PyQt5 import QtGui, QtCore

from PyQt5.uic import loadUi
import sys

from os import getpid, getppid, listdir, system, kill
# import signals SIGKILL
import signal

from os.path import isfile, join
import threading
# import QThread
from PyQt5.QtCore import QThread, pyqtSignal
import qdarktheme


dir_path = "/home/ahmed/Documents/GitHub/Adaptive/build/App/processes/redirected"

class MyThread(QThread):
    new_signal = pyqtSignal(list)

    def __init__(self, path=None, opend=None, parent=None):
        super(QThread, self).__init__(parent)
        self.path = path
        self.opened=opend
        
    def detect_new_file(self,dir_path):
        files = [f for f in listdir(dir_path) if isfile(join(dir_path, f)) and f not in self.opened]
        if len(files) > 0:
            self.opened+=files
            return files
        else:
            return None
        
    def run(self):
        while True:
            k = self.detect_new_file(self.path)
            if k is not None:
                self.new_signal.emit(k)

class fileThread(QThread):
    #create signal of type string and int
    new_signal = pyqtSignal(str, int)
    def __init__(self, path=None,index =0, parent=None):
        super(QThread, self).__init__(parent)
        self.path = path
        self.index = index
    def run(self):
        file = open(self.path, "rt")
        while True:
            where = file.tell()
            data = file.read()
            if not data:
                file.seek(where)
                continue
            self.new_signal.emit(data,self.index)


class QCustomTabWidget (QtWidgets.QTabWidget):
    def __init__ (self, parent = None):
        super(QCustomTabWidget, self).__init__(parent)
        self.setTabsClosable(True)
        self.tabCloseRequested.connect(self.closeTab)
        for i in range(1, 10):
            self.addTab(QtGui.QWidget(), 'Tab %d' % i)

    def closeTab (self, currentIndex):
        currentQWidget = self.widget(currentIndex)
        currentQWidget.deleteLater()
        self.removeTab(currentIndex)
        
# create class as thread to run external process
class MyProcess(QThread):
    #create signal of type process handle
    new_signal = pyqtSignal(int)
    def __init__(self, path=None, parent=None):
        super(QThread, self).__init__(parent)
        self.path = path
    def run(self):
        # run the process in another terminal and save the handle of the terminal
        self.process = system("gnome-terminal -e 'bash -c \"cd "+self.path+" && ./run.sh; exec bash\"'")
        # self.new_signal.emit(self.process)
            


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.showMaximized()
        self.setWindowTitle("Editory")
        self.setWindowIcon(QtGui.QIcon('favicon.png'))

        self.current_editor = self.create_editor()
        self.editors = []

        self.tab_widget = QtWidgets.QTabWidget()
        self.tab_widget.setTabsClosable(False)
        self.tab_widget.currentChanged.connect(self.change_text_editor)
        # self.tab_widget.tabCloseRequested.connect(self.remove_editor)
        # self.new_document()
        self.setCentralWidget(self.tab_widget)

        # self.configure_menuBar()
        self.configure_toolbar()
        self.opened_files = []
        self.new_files = []
        self.threads_f = []
        self.thread = MyThread(dir_path, self.opened_files)
        self.thread.new_signal.connect(self.printdata)
        self.thread.start()
        
        
    def printdata(self, k):
        for f in k:
            self.new_document(title = f)
            index  = self.editors.index(self.current_editor)
            
            
            self.threads_f.append(fileThread(join(dir_path,f),index))
            self.threads_f[-1].new_signal.connect(self.handle_file_newdata)
            self.threads_f[-1].start()
            print(f)
            
    def handle_file_newdata(self, data, index):
        self.editors[index].moveCursor(QtGui.QTextCursor.End)
        self.editors[index].insertPlainText(data)
        

    def handle_app_newdata(self, process):
        print("process ", process)
        self.process = process

    def Start_APP(self):
        self.thread_app = MyProcess("/home/ahmed/Documents/GitHub/Adaptive/quick_test")
        self.thread_app.new_signal.connect(self.handle_app_newdata)
        self.thread_app.start()
        
        # run terminal command in another threed 
        # self.ter = system("/home/ahmed/Documents/GitHub/Adaptive/quick_test/run.sh")

        
    def Terminate_APP(self):
        # send kill signal to the process
        kill(self.process, signal.SIGKILL)
        
        # send kill signal to process
        # kill(self.ter, signal.SIGKILL)
        
    def configure_toolbar(self):
        items = (('icons/start.png', 'Start', self.Start_APP),
            ('icons/stop.png', 'Open', self.Terminate_APP),
            None,
            ('icons/exit.png', 'Quit', self.quit),
        )

        

        self.toolbar = self.addToolBar("Toolbar")

        for item in items:
            if item:
                icon, text, callback = item
                action = QtWidgets.QAction(QtGui.QIcon(icon), text, self)
                action.triggered.connect(callback)
                self.toolbar.addAction(action)
            else :
                self.toolbar.addSeparator()


    def create_editor(self):
        text_editor = QtWidgets.QTextEdit()
        text_editor.setTabStopWidth(12)
        return text_editor

    def change_text_editor(self, index):
        if index < len(self.editors):
            self.current_editor = self.editors[index]

    # Input Functions
    def new_document(self, checked = False, title = "Untitled"):
        self.current_editor = self.create_editor()
        self.editors.append(self.current_editor)
        self.tab_widget.addTab(self.current_editor, title + str(len(self.editors)))
        self.tab_widget.setCurrentWidget(self.current_editor)


    def quit(self): self.close()


def run():
    app = QApplication(sys.argv)
    GUI = Window()

    app.setStyleSheet(qdarktheme.load_stylesheet())

    sys.exit(app.exec_())



if __name__ == '__main__':
    run()
