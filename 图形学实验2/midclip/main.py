import sys
from PySide2.QtWidgets import *
from PySide2.QtGui import *
from PySide2.QtCore import *
from form import *


class DrawingWidget(QWidget, Ui_Form):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setupUi(self)

        self.l = int(self.lineEdit_left.text())
        self.t = int(self.lineEdit_top.text())
        self.w = int(self.lineEdit_width.text())
        self.h = int(self.lineEdit_height.text())

        self.x0 = int(self.lineEdit_x0.text())
        self.y0 = int(self.lineEdit_y0.text())
        self.x1 = int(self.lineEdit_x1.text())
        self.y1 = int(self.lineEdit_y1.text())

        self.rect_color = self.pushButton_rect_color.palette().background().color()
        self.new_rect_color = self.rect_color
        self.pushButton_rect_color.setPalette(QPalette(self.rect_color))

        self.line_color = self.pushButton_line_color.palette().background().color()
        self.new_line_color = self.line_color
        self.pushButton_line_color.setPalette(QPalette(self.line_color))

        self.clip_color = self.pushButton_clip_color.palette().background().color()
        self.new_clip_color = self.clip_color
        self.pushButton_clip_color.setPalette(QPalette(self.clip_color))


    def onRColor(self):
        self.new_rect_color = QColorDialog.getColor()
        self.pushButton_rect_color.setPalette(QPalette(self.new_rect_color))

    def onLColor(self):
        self.new_line_color = QColorDialog.getColor()
        self.pushButton_line_color.setPalette(QPalette(self.new_line_color))

    def onCColor(self):
        self.new_clip_color = QColorDialog.getColor()
        self.pushButton_clip_color.setPalette(QPalette(self.new_clip_color))

    def onOk(self):
        self.l = int(self.lineEdit_left.text())
        self.t = int(self.lineEdit_top.text())
        self.w = int(self.lineEdit_width.text())
        self.h = int(self.lineEdit_height.text())

        self.x0 = int(self.lineEdit_x0.text())
        self.y0 = int(self.lineEdit_y0.text())
        self.x1 = int(self.lineEdit_x1.text())
        self.y1 = int(self.lineEdit_y1.text())

        self.rect_color = self.new_rect_color
        self.line_color = self.new_line_color
        self.clip_color = self.new_clip_color
        self.update()

    def paintEvent(self, event):
        w = self.groupBox_set.width()

        self.groupBox_set.move(self.width()-w-10, 10)

        qp = QPainter()
        qp.begin(self)
        self.draw(qp)
        qp.end()

    def draw(self, qp):
        rect = QRect(self.l, self.t, self.w, self.h)
        line = QLine(self.x0, self.y0, self.x1, self.y1)

        qp.save()
        qp.setPen(self.rect_color)
        qp.drawRect(rect)
        qp.restore()

        qp.save()
        qp.setPen(self.line_color)
        qp.drawLine(line)
        qp.restore()

        qp.save()
        qp.setPen(self.clip_color)
        line1 = self.line_clip(line, rect)
        qp.drawLine(line1)
        qp.restore()

    def getcode(self, pos, rect):
        code = 0
        x = pos.x()
        y = pos.y()

        if x < rect.left():
            code = code | 0x01
        else:
            code = code & 0xfe

        if x > rect.right():
            code = code | 0x02
        else:
            code = code & 0xfd

        if y < rect.top():
            code = code | 0x04
        else:
            code = code & 0xfb

        if y > rect.bottom():
            code = code | 0x08
        else:
            code = code & 0xf7

        return code

    def line_clip(self, line1, rt):
        done = False  # 裁剪完成标志
        p1 = line1.p1()
        p2 = line1.p2()
        c1 = self.getcode(p1, rt)
        c2 = self.getcode(p2, rt)
        p = QPoint(0, 0)
        line2 = QLine(p, p)


        if c1 == 0 and c2 == 0:  # 线段完全可见
            line2 = QLine(p1, p2)
        elif c1 & c2 != 0:  # 线段完全不可见
            line2 = QLine(QPoint(0, 0), QPoint(0, 0))
        else:  # 部分可见
            ## 寻找P1的最远可见点
            if c2 != 0:  # p2不可见
                p11 = p1
                p22 = p2
                pmid = QPoint((p11.x() + p22.x()) / 2, (p11.y() + p22.y()) / 2)
                while (abs(p11.x() - pmid.x()) > 1 or abs(p11.y() - pmid.y()) > 1):
                    # pmid = (p11 + p22) / 2
                    cmid = self.getcode(pmid, rt)
                    if cmid == 0:
                        p11 = pmid
                    else:
                        p22 = pmid

                    pmid = QPoint((p11.x() + p22.x()) / 2, (p11.y() + p22.y()) / 2)

                p2 = pmid

            ## 寻找P2的最远可见点
            if c1 != 0:  # p1不可见
                p11 = p1
                p22 = p2
                pmid = QPoint((p11.x() + p22.x()) / 2, (p11.y() + p22.y()) / 2)
                while (abs(p11.x() - pmid.x()) > 1 or abs(p11.y() - pmid.y()) > 1):
                    # pmid = (p11 + p22) / 2
                    cmid = self.getcode(pmid, rt)
                    if cmid == 0:
                        p22 = pmid
                    else:
                        p11 = pmid

                    pmid = QPoint((p11.x() + p22.x()) / 2, (p11.y() + p22.y()) / 2)

                p1 = pmid

            line2 = QLine(p1, p2)

        return line2



if __name__=="__main__":
    app = QApplication(sys.argv)
    win = DrawingWidget()
    win.show()
    sys.exit(app.exec_())