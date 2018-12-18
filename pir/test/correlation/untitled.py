#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Untitled
# Generated: Fri Jun 15 14:28:50 2018
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import sip
import sys


class untitled(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Untitled")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Untitled")
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "untitled")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.signal_len = signal_len = 294
        self.samp_rate = samp_rate = 1000
        self.header_mod = header_mod = digital.constellation_bpsk()

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_time_sink_x_0_1 = qtgui.time_sink_c(
        	samp_rate, #size
        	samp_rate, #samp_rate
        	"Correlation", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0_1.set_update_time(0.10)
        self.qtgui_time_sink_x_0_1.set_y_axis(-10, 150)
        
        self.qtgui_time_sink_x_0_1.set_y_label("Amplitude", "")
        
        self.qtgui_time_sink_x_0_1.enable_tags(-1, True)
        self.qtgui_time_sink_x_0_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_1.enable_autoscale(False)
        self.qtgui_time_sink_x_0_1.enable_grid(False)
        self.qtgui_time_sink_x_0_1.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_0_1.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [3, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(2*1):
            if len(labels[i]) == 0:
                if(i % 2 == 0):
                    self.qtgui_time_sink_x_0_1.set_line_label(i, "Re{{Data {0}}}".format(i/2))
                else:
                    self.qtgui_time_sink_x_0_1.set_line_label(i, "Im{{Data {0}}}".format(i/2))
            else:
                self.qtgui_time_sink_x_0_1.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_1.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_1.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_1.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_1.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_1.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_0_1_win = sip.wrapinstance(self.qtgui_time_sink_x_0_1.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_1_win)
        self.qtgui_time_sink_x_0_0 = qtgui.time_sink_c(
        	294, #size
        	samp_rate, #samp_rate
        	"Original", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0_0.set_y_axis(-1.5, 1.5)
        
        self.qtgui_time_sink_x_0_0.set_y_label("Amplitude", "")
        
        self.qtgui_time_sink_x_0_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0_0.enable_grid(False)
        self.qtgui_time_sink_x_0_0.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_0_0.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [3, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(2*1):
            if len(labels[i]) == 0:
                if(i % 2 == 0):
                    self.qtgui_time_sink_x_0_0.set_line_label(i, "Re{{Data {0}}}".format(i/2))
                else:
                    self.qtgui_time_sink_x_0_0.set_line_label(i, "Im{{Data {0}}}".format(i/2))
            else:
                self.qtgui_time_sink_x_0_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_0_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_0_win)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_c(
        	samp_rate, #size
        	samp_rate, #samp_rate
        	"Out", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1.5, 1.5)
        
        self.qtgui_time_sink_x_0.set_y_label("Amplitude", "")
        
        self.qtgui_time_sink_x_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_0.disable_legend()
        
        labels = ["", "", "", "", "",
                  "", "", "", "", ""]
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [3, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(2*1):
            if len(labels[i]) == 0:
                if(i % 2 == 0):
                    self.qtgui_time_sink_x_0.set_line_label(i, "Re{{Data {0}}}".format(i/2))
                else:
                    self.qtgui_time_sink_x_0.set_line_label(i, "Im{{Data {0}}}".format(i/2))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_win)
        self.digital_corr_est_cc_0 = digital.corr_est_cc(((1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,0,1,1,1,0,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,1,1,1,1,1,0,1,0,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1)), 1, 0, 0.9)
        self.blocks_vector_source_x_0 = blocks.vector_source_c((1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,0,0,1,1,1,0,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,1,1,1,1,1,0,1,0,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1.0,0.5403023058681398,-0.4161468365471424,-0.9899924966004454,-0.6536436208636119,0.28366218546322625,0.960170286650366,0.7539022543433046,-0.14550003380861354,-0.9111302618846769,-0.8390715290764524,0.004425697988050785,0.8438539587324921,0.9074467814501962,0.1367372182078336,-0.7596879128588213,-0.9576594803233847,-0.27516333805159693,0.6603167082440802,0.9887046181866692,0.40808206181339196,-0.5477292602242684,-0.9999608263946371,-0.5328330203333975,0.424179007336997,0.9912028118634736,0.6469193223286404,-0.2921388087338362,-0.9626058663135666,-0.7480575296890003,0.15425144988758405,0.9147423578045313,0.8342233605065102,-0.013276747223059479,-0.8485702747846052,-0.9036922050915067,-0.12796368962740468,0.7654140519453434,0.9550736440472949,0.26664293235993725,-0.6669380616522619,-0.9873392775238264,-0.39998531498835127,0.5551133015206257,0.9998433086476912,0.5253219888177297,-0.4321779448847783,-0.9923354691509287,-0.6401443394691997,0.3005925437436371,0.9649660284921133,0.7421541968137826,-0.16299078079570548,-0.9182827862121189,-0.8293098328631502,0.022126756261955736,0.8532201077225842,0.8998668269691937,0.11918013544881928,-0.7710802229758452,-0.9524129804151563,-0.25810163593826746,0.6735071623235862,0.9858965815825497,0.39185723042955,-0.562453851238172,-0.99964745596635,-0.5177697997895051,0.4401430224960407,0.9933903797222716,0.6333192030862999,-0.3090227281660707,-0.9672505882738824,-0.7361927182273159,0.17171734183077755,0.9217512697247493,0.8243313311075577,-0.03097503173121646,-0.8578030932449878,-0.8959709467909631,-0.11038724383904756,0.7766859820216312,0.9496776978825432,0.24954011797333814,-0.6800234955873388,-0.9843766433940419,-0.38369844494974187,0.569750334265312,0.9993732836951247,0.5101770449416689,-0.4480736161291701,-0.9943674609282015,-0.626444447910339,0.31742870151970165,0.9694593666699876,0.7301735609948197,-0.18043044929108396,-0.9251475365964139,-0.8192882452914593,0.0398208803931389,0.8623188722876839,0.8920048697881602,0.10158570369662134,-0.7822308898871159,-0.9468680107512125,-0.24095904923620143,0.6864865509069841,0.9827795820412206,0.3755095977670121,-0.577002178942952,-0.999020813314648,-0.5025443191453852,0.4559691044442761,0.9952666362171313,0.6195206125592099,-0.3258098052199642,-0.9715921906288022,-0.7240971967004738,0.1891294205289584,0.9284713207390763,0.8141809705265618,-0.04866360920015389,-0.8667670910519801,-0.8879689066918555,-0.09277620459766088,0.7877145121442345,0.9439841391523142,0.23235910202965793,-0.6928958219201651,-0.9811055226493881,-0.3672913304546965,0.5842088171092893,0.9985900724399912,0.4948722204034305,-0.4638288688518717,-0.9960878351411849,-0.6125482394960996,0.33416538263076073,0.9736488930495181,0.717964101410472,-0.19781357400426822,-0.9317223617435201,-0.8090099069535975,0.05750252534912421,0.8711474010323434,0.8838633737085002,0.08395943674184847,-0.7931364191664784,-0.9410263090291437,-0.22374095013558368), True, 1, [])
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_throttle_0, 0), (self.qtgui_time_sink_x_0_0, 0))    
        self.connect((self.blocks_vector_source_x_0, 0), (self.blocks_throttle_0, 0))    
        self.connect((self.blocks_vector_source_x_0, 0), (self.digital_corr_est_cc_0, 0))    
        self.connect((self.digital_corr_est_cc_0, 0), (self.qtgui_time_sink_x_0, 0))    
        self.connect((self.digital_corr_est_cc_0, 1), (self.qtgui_time_sink_x_0_1, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "untitled")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()


    def get_signal_len(self):
        return self.signal_len

    def set_signal_len(self, signal_len):
        self.signal_len = signal_len

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.qtgui_time_sink_x_0_0.set_samp_rate(self.samp_rate)
        self.qtgui_time_sink_x_0_1.set_samp_rate(self.samp_rate)

    def get_header_mod(self):
        return self.header_mod

    def set_header_mod(self, header_mod):
        self.header_mod = header_mod


def main(top_block_cls=untitled, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
