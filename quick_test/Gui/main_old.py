from PyQt5.QtWidgets import QMainWindow, QApplication, QFileDialog
from PyQt5 import QtWidgets
from PyQt5 import QtGui, QtCore
 
from PyQt5.uic import loadUi
import sys

from os import listdir, system, kill
# import signals SIGKILL
import signal

from os.path import isfile, join
import threading
# import QThread
from PyQt5.QtCore import QThread, pyqtSignal


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

        


class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.showMaximized()
        self.setWindowTitle("Editory")
        self.setWindowIcon(QtGui.QIcon('favicon.png'))

        self.current_editor = self.create_editor()
        self.editors = []

        self.tab_widget = QtWidgets.QTabWidget()
        self.tab_widget.setTabsClosable(True)
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
        
        

    def configure_menuBar(self):
        menubar = self.menuBar()

        menubar_items = {
            '&File': [
                ("&New", "Ctrl+N", self.new_document),
                ("&Open", "Ctrl+O", self.open_document),
                ("&Save", "Ctrl+S", self.save_document),
                ("&Print", "Ctrl+P", self.print_document),
                None,
                ("&Quit", "Ctrl+Q", self.quit),
            ],
            '&Edit': [
                ("&Cut", "Ctrl+X", self.cut_document),
                ("&Copy", "Ctrl+C", self.copy_document),
                ("&Paste", "Ctrl+V", self.paste_document),
                None,
                ("&Undo", "Ctrl+Z", self.undo_document),
                ("&Redo", "Ctrl+Y", self.redo_document)
            ],
            '&View': [
                ("&Fullscreen", "F11", self.fullscreen),
                None,
                ("&Align Left", "", self.align_left),
                ("&Align Right", "", self.align_right),
                ("&Align Center", "", self.align_center),
                ("&Align Justify", "", self.align_justify)
            ]
        }

        for menuitem, actions in menubar_items.items():
            menu = menubar.addMenu(menuitem)
            for act in actions:
                if act:
                    text, shorcut, callback = act
                    action = QtWidgets.QAction(text, self)
                    action.setShortcut(shorcut)
                    action.triggered.connect(callback)
                    menu.addAction(action)
                else :
                    menu.addSeparator()

        # Font Family Input
        fontBox = QtWidgets.QFontComboBox(self)
        fontBox.currentFontChanged.connect(self.FontFamily)

        fontSize = QtWidgets.QComboBox(self)
        fontSize.setEditable(True)
        fontSize.setMinimumContentsLength(3)

        fontSize.activated.connect(self.FontSize)

        # Font Sizes
        fontSizes = ['6', '7', '8', '9', '10', '11', '12', '13', '14',
            '15', '16', '18', '20', '22', '24', '26', '28',
            '32', '36', '40', '44', '48', '54', '60', '66',
            '72', '80', '88', '96'
        ]

        fontSize.addItems(fontSizes)
        font_family = QtWidgets.QWidgetAction(self)
        font_family.setDefaultWidget(fontBox)
        # Settings Menubar
        settings = menubar.addMenu('&Settings')
        menu_font = settings.addMenu("&Font")
        menu_font.addAction(font_family)

        font_size = QtWidgets.QWidgetAction(self)
        font_size.setDefaultWidget(fontSize)
        menu_size = settings.addMenu("&Font Size")
        menu_size.addAction(font_size)

    def Start_APP(self):
        # run terminal command 
        self.ter = system("/home/ahmed/Documents/GitHub/Adaptive/quick_test/run.sh")
        
    def Terminate_APP(self):
        # send kill signal to process
        kill(self.ter, signal.SIGKILL)
        
    def configure_toolbar(self):
        items = (('icons/new.png', 'Start', self.Start_APP),
            ('icons/open.png', 'Open', self.Terminate_APP),
            None,
            ('icons/quit.png', 'Quit', self.quit),
        )

        # items = (('icons/new.png', 'New', self.new_document),
        #     ('icons/open.png', 'Open', self.open_document),
        #     ('icons/save.png', 'Save', self.save_document),
        #     None,
        #     ('icons/cut.png', 'Cut', self.cut_document),
        #     ('icons/copy.png', 'Copy', self.copy_document),
        #     ('icons/paste.png', 'Paste', self.paste_document),
        #     None,
        #     ('icons/undo.png', 'Undo', self.undo_document),
        #     ('icons/redo.png', 'Redo', self.redo_document),
        #     None,
        #     ('icons/print.png', 'Print', self.print_document),
        #     None,
        #     ('icons/quit.png', 'Quit', self.quit),
        # )

        self.toolbar = self.addToolBar("Toolbar")

        for item in items:
            if item:
                icon, text, callback = item
                action = QtWidgets.QAction(QtGui.QIcon(icon), text, self)
                action.triggered.connect(callback)
                self.toolbar.addAction(action)
            else :
                self.toolbar.addSeparator()

    # def remove_editor(self, index):
    #     self.tab_widget.removeTab(index)
    #     if index < len(self.editors):
    #         del self.editors[index]

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

    def open_document(self):
        filename = QtWidgets.QFileDialog.getOpenFileName(self, 'Open File')
        if filename:
            f = open(filename, 'r')
        filedata = f.read()
        self.new_document(title = filename)
        self.current_editor.setText(filedata)
        f.close()

    def save_document(self):
        name = QtWidgets.QFileDialog.getSaveFileName(self, 'Save File')
        file = open(name, 'w')
        if file:
            text = self.current_editor.toPlainText()
            file.write(text)
            file.close()

    def print_document(self):
        print_dialog = QtWidgets.QPrintDialog()
        if print_dialog.exec_() == QtWidgets.QDialog.Accepted:
            self.current_editor.document().print_(print_dialog.printer())

    def quit(self): self.close()

    def undo_document(self): self.current_editor.undo()

    def redo_document(self): self.current_editor.redo()

    def cut_document(self): self.current_editor.cut()

    def copy_document(self): self.current_editor.copy()

    def paste_document(self): self.current_editor.paste()

    def align_left(self): self.current_editor.setAlignment(Qt.AlignLeft)

    def align_right(self): self.current_editor.setAlignment(Qt.AlignRight)

    def align_center(self): self.current_editor.setAlignment(Qt.AlignCenter)

    def align_justify(self):
        self.current_editor.setAlignment(Qt.AlignJustify)

    def fullscreen(self):
        if not self.isFullScreen():
            self.showFullScreen()
        else :
            self.showMaximized()

    def FontFamily(self, font):
        self.current_editor.setCurrentFont(font)

    def FontSize(self, fontsize):
        self.current_editor.setFontPointSize(int(fontsize))





def run():
    app = QApplication(sys.argv)
    GUI = Window()

    
    sys.exit(app.exec_())




run()