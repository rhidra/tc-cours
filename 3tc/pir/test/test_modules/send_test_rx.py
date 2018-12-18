#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Send Test Rx
# Generated: Fri Jun 15 15:51:28 2018
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import fft
from gnuradio import gr
from gnuradio import uhd
from gnuradio.digital.utils import tagged_streams
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from optparse import OptionParser
import pir
import time


class send_test_rx(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Send Test Rx")

        ##################################################
        # Variables
        ##################################################
        self.pilot_symbols = pilot_symbols = ((1, 1, 1, -1,),)
        self.pilot_carriers = pilot_carriers = ((-21, -7, 7, 21,),)
        self.payload_mod = payload_mod = digital.constellation_qpsk()
        self.packet_length_tag_key = packet_length_tag_key = "packet_len"
        self.occupied_carriers = occupied_carriers = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 27),)
        self.length_tag_key = length_tag_key = "frame_len"
        self.header_mod = header_mod = digital.constellation_bpsk()
        self.fft_len = fft_len = 64
        self.sync_word2 = sync_word2 = [0j, 0j, 0j, 0j, 0j, 0j, (-1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), (1+0j), (1+0j), (1 +0j), (1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), 0j, (1+0j), (-1+0j), (1+0j), (1+0j), (1+0j), (-1+0j), (1+0j), (1+0j), (1+0j), (-1+0j), (1+0j), (1+0j), (1+0j), (1+0j), (-1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (-1+0j), 0j, 0j, 0j, 0j, 0j]
        self.sync_word1 = sync_word1 = [0., 0., 0., 0., 0., 0., 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 0., 0., 0., 0., 0.]
        self.samp_rate = samp_rate = 5000000
        self.rolloff = rolloff = 0
        self.payload_equalizer = payload_equalizer = digital.ofdm_equalizer_simpledfe(fft_len, payload_mod.base(), occupied_carriers, pilot_carriers, pilot_symbols, 1)
        self.packet_len = packet_len = 96
        self.header_formatter = header_formatter = digital.packet_header_ofdm(occupied_carriers, n_syms=1, len_tag_key=packet_length_tag_key, frame_len_tag_key=length_tag_key, bits_per_header_sym=header_mod.bits_per_symbol(), bits_per_payload_sym=payload_mod.bits_per_symbol(), scramble_header=False)
        self.header_equalizer = header_equalizer = digital.ofdm_equalizer_simpledfe(fft_len, header_mod.base(), occupied_carriers, pilot_carriers, pilot_symbols)

        ##################################################
        # Blocks
        ##################################################
        self.uhd_usrp_source_0 = uhd.usrp_source(
        	",".join(("serial=30CEECB", "")),
        	uhd.stream_args(
        		cpu_format="fc32",
        		channels=range(1),
        	),
        )
        self.uhd_usrp_source_0.set_samp_rate(samp_rate)
        self.uhd_usrp_source_0.set_center_freq(2.492e9, 0)
        self.uhd_usrp_source_0.set_gain(40, 0)
        self.uhd_usrp_source_0.set_antenna("TX/RX", 0)
        self.pir_get_timestamp_delta_cm_0 = pir.get_timestamp_delta_cm()
        self.fft_vxx_0 = fft.fft_vcc(fft_len, True, (()), True, 1)
        self.digital_packet_headerparser_b_0 = digital.packet_headerparser_b(header_formatter.base())
        self.digital_ofdm_sync_sc_cfb_0 = digital.ofdm_sync_sc_cfb(fft_len, fft_len/4, False)
        self.digital_ofdm_serializer_vcc_header_0 = digital.ofdm_serializer_vcc(fft_len, occupied_carriers, length_tag_key, "", 0, "", True)
        self.digital_ofdm_serializer_vcc_header = digital.ofdm_serializer_vcc(fft_len, occupied_carriers, length_tag_key, "", 0, "", True)
        self.digital_ofdm_frame_equalizer_vcvc_0 = digital.ofdm_frame_equalizer_vcvc(header_equalizer.base(), fft_len/4, length_tag_key, True, 1)
        self.digital_ofdm_chanest_vcvc_0 = digital.ofdm_chanest_vcvc((sync_word1), (sync_word2), 1, 0, 3, False)
        self.digital_header_payload_demux_0 = digital.header_payload_demux(
        	  3,
        	  fft_len,
        	  fft_len/4,
        	  length_tag_key,
        	  "",
        	  True,
        	  gr.sizeof_gr_complex,
        	  "rx_time",
                  samp_rate,
                  (),
            )
        self.digital_corr_est_cc_0 = digital.corr_est_cc(((0.00000 - 0.00000j, -0.23756 + 0.06817j, 0.02455 - 0.06790j, -0.02923 + 0.05414j, 0.00701 - 0.10558j, 0.07080 - 0.00739j, 0.04334 + 0.00660j, -0.11691 + 0.08759j, 0.09375 + 0.06250j, 0.04313 - 0.10143j, 0.00862 - 0.03317j, -0.05702 + 0.07170j, -0.09857 - 0.09157j, 0.02654 + 0.03204j, -0.03675 - 0.04537j, 0.06443 + 0.17533j, 0.04419 + 0.00000j, 0.06443 - 0.17533j, -0.03675 + 0.04537j, 0.02654 - 0.03204j, -0.09857 + 0.09157j, -0.05702 - 0.07170j, 0.00862 + 0.03317j, 0.04313 + 0.10143j, 0.09375 - 0.06250j, -0.11691 - 0.08759j, 0.04334 - 0.00660j, 0.07080 + 0.00739j, 0.00701 + 0.10558j, -0.02923 - 0.05414j, 0.02455 + 0.06790j, -0.23756 - 0.06817j, 0.00000 + 0.00000j, 0.23756 - 0.06817j, -0.02455 + 0.06790j, 0.02923 - 0.05414j, -0.00701 + 0.10558j, -0.07080 + 0.00739j, -0.04334 - 0.00660j, 0.11691 - 0.08759j, -0.09375 - 0.06250j, -0.04313 + 0.10143j, -0.00862 + 0.03317j, 0.05702 - 0.07170j, 0.09857 + 0.09157j, -0.02654 - 0.03204j, 0.03675 + 0.04537j, -0.06443 - 0.17533j, -0.04419 + 0.00000j, -0.06443 + 0.17533j, 0.03675 - 0.04537j, -0.02654 + 0.03204j, 0.09857 - 0.09157j, 0.05702 + 0.07170j, -0.00862 - 0.03317j, -0.04313 - 0.10143j, -0.09375 + 0.06250j, 0.11691 + 0.08759j, -0.04334 + 0.00660j, -0.07080 - 0.00739j, -0.00701 - 0.10558j, 0.02923 + 0.05414j, -0.02455 - 0.06790j, 0.23756 + 0.06817j, 0.00000 - 0.00000j, -0.23756 + 0.06817j, 0.02455 - 0.06790j, -0.02923 + 0.05414j, 0.00701 - 0.10558j, 0.07080 - 0.00739j, 0.04334 + 0.00660j, -0.11691 + 0.08759j, 0.09375 + 0.06250j, 0.04313 - 0.10143j, 0.00862 - 0.03317j, -0.05702 + 0.07170j, -0.09857 - 0.09157j, 0.02654 + 0.03204j, -0.03675 - 0.04537j, 0.06443 + 0.17533j, 0.06250 + 0.03125j, -0.10790 - 0.08255j, 0.00182 + 0.03337j, 0.09586 - 0.07711j, 0.06872 + 0.05573j, 0.00373 + 0.04257j, -0.03565 - 0.03853j, -0.14193 + 0.01821j, -0.15089 - 0.03504j, 0.14492 - 0.01154j, 0.07984 + 0.05798j, -0.06544 - 0.02403j, 0.10927 - 0.05236j, 0.14303 + 0.12879j, -0.04601 - 0.13003j, -0.11594 + 0.05444j, -0.06250 + 0.00000j, -0.11594 - 0.05444j, -0.04601 + 0.13003j, 0.14303 - 0.12879j, 0.10927 + 0.05236j, -0.06544 + 0.02403j, 0.07984 - 0.05798j, 0.14492 + 0.01154j, -0.15089 + 0.03504j, -0.14193 - 0.01821j, -0.03565 + 0.03853j, 0.00373 - 0.04257j, 0.06872 - 0.05573j, 0.09586 + 0.07711j, 0.00182 - 0.03337j, -0.10790 + 0.08255j, 0.06250 - 0.03125j, -0.00527 - 0.11799j, 0.00182 + 0.05304j, 0.05923 + 0.02687j, -0.09460 + 0.11347j, 0.06227 - 0.14667j, -0.03565 + 0.03377j, -0.10488 - 0.05448j, 0.02589 + 0.09754j, 0.06134 - 0.07480j, 0.07984 + 0.06226j, -0.02766 + 0.02419j, 0.04162 - 0.02844j, -0.09425 - 0.14799j, -0.04601 + 0.09145j, 0.09289 + 0.12172j, -0.06250 + 0.00000j, 0.09289 - 0.12172j, -0.04601 - 0.09145j, -0.09425 + 0.14799j, 0.04162 + 0.02844j, -0.02766 - 0.02419j, 0.07984 - 0.06226j, 0.06134 + 0.07480j, 0.02589 - 0.09754j, -0.10488 + 0.05448j, -0.03565 - 0.03377j, 0.06227 + 0.14667j, -0.09460 - 0.11347j, 0.05923 - 0.02687j, 0.00182 - 0.05304j, -0.00527 + 0.11799j, 0.06250 + 0.03125j, -0.10790 - 0.08255j, 0.00182 + 0.03337j, 0.09586 - 0.07711j, 0.06872 + 0.05573j, 0.00373 + 0.04257j, -0.03565 - 0.03853j, -0.14193 + 0.01821j, -0.15089 - 0.03504j, 0.14492 - 0.01154j, 0.07984 + 0.05798j, -0.06544 - 0.02403j, 0.10927 - 0.05236j, 0.14303 + 0.12879j, -0.04601 - 0.13003j, -0.11594 + 0.05444j)), 1, 0, 0.999999999)
        self.digital_constellation_decoder_cb_0 = digital.constellation_decoder_cb(header_mod.base())
        self.blocks_tag_gate_0 = blocks.tag_gate(gr.sizeof_gr_complex * 1, False)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_message_debug_0 = blocks.message_debug()
        self.blocks_delay_0 = blocks.delay(gr.sizeof_gr_complex*1, fft_len+fft_len/4)
        self.analog_frequency_modulator_fc_0 = analog.frequency_modulator_fc(-2.0/fft_len)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.digital_packet_headerparser_b_0, 'header_data'), (self.digital_header_payload_demux_0, 'header_data'))    
        self.msg_connect((self.pir_get_timestamp_delta_cm_0, 'out'), (self.blocks_message_debug_0, 'print'))    
        self.connect((self.analog_frequency_modulator_fc_0, 0), (self.blocks_multiply_xx_0, 0))    
        self.connect((self.blocks_delay_0, 0), (self.blocks_multiply_xx_0, 1))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.digital_corr_est_cc_0, 0))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.digital_header_payload_demux_0, 0))    
        self.connect((self.blocks_tag_gate_0, 0), (self.blocks_delay_0, 0))    
        self.connect((self.blocks_tag_gate_0, 0), (self.digital_ofdm_sync_sc_cfb_0, 0))    
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.digital_packet_headerparser_b_0, 0))    
        self.connect((self.digital_corr_est_cc_0, 0), (self.pir_get_timestamp_delta_cm_0, 0))    
        self.connect((self.digital_header_payload_demux_0, 1), (self.digital_ofdm_serializer_vcc_header_0, 0))    
        self.connect((self.digital_header_payload_demux_0, 0), (self.fft_vxx_0, 0))    
        self.connect((self.digital_ofdm_chanest_vcvc_0, 0), (self.digital_ofdm_frame_equalizer_vcvc_0, 0))    
        self.connect((self.digital_ofdm_frame_equalizer_vcvc_0, 0), (self.digital_ofdm_serializer_vcc_header, 0))    
        self.connect((self.digital_ofdm_serializer_vcc_header, 0), (self.digital_constellation_decoder_cb_0, 0))    
        self.connect((self.digital_ofdm_serializer_vcc_header_0, 0), (self.blocks_null_sink_0, 0))    
        self.connect((self.digital_ofdm_sync_sc_cfb_0, 0), (self.analog_frequency_modulator_fc_0, 0))    
        self.connect((self.digital_ofdm_sync_sc_cfb_0, 1), (self.digital_header_payload_demux_0, 1))    
        self.connect((self.fft_vxx_0, 0), (self.digital_ofdm_chanest_vcvc_0, 0))    
        self.connect((self.uhd_usrp_source_0, 0), (self.blocks_tag_gate_0, 0))    

    def get_pilot_symbols(self):
        return self.pilot_symbols

    def set_pilot_symbols(self, pilot_symbols):
        self.pilot_symbols = pilot_symbols
        self.set_header_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_pilot_carriers(self):
        return self.pilot_carriers

    def set_pilot_carriers(self, pilot_carriers):
        self.pilot_carriers = pilot_carriers
        self.set_header_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_payload_mod(self):
        return self.payload_mod

    def set_payload_mod(self, payload_mod):
        self.payload_mod = payload_mod
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_packet_length_tag_key(self):
        return self.packet_length_tag_key

    def set_packet_length_tag_key(self, packet_length_tag_key):
        self.packet_length_tag_key = packet_length_tag_key
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))

    def get_occupied_carriers(self):
        return self.occupied_carriers

    def set_occupied_carriers(self, occupied_carriers):
        self.occupied_carriers = occupied_carriers
        self.set_header_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_length_tag_key(self):
        return self.length_tag_key

    def set_length_tag_key(self, length_tag_key):
        self.length_tag_key = length_tag_key
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))

    def get_header_mod(self):
        return self.header_mod

    def set_header_mod(self, header_mod):
        self.header_mod = header_mod
        self.set_header_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))

    def get_fft_len(self):
        return self.fft_len

    def set_fft_len(self, fft_len):
        self.fft_len = fft_len
        self.set_header_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))
        self.analog_frequency_modulator_fc_0.set_sensitivity(-2.0/self.fft_len)
        self.blocks_delay_0.set_dly(self.fft_len+self.fft_len/4)

    def get_sync_word2(self):
        return self.sync_word2

    def set_sync_word2(self, sync_word2):
        self.sync_word2 = sync_word2

    def get_sync_word1(self):
        return self.sync_word1

    def set_sync_word1(self, sync_word1):
        self.sync_word1 = sync_word1

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)

    def get_rolloff(self):
        return self.rolloff

    def set_rolloff(self, rolloff):
        self.rolloff = rolloff

    def get_payload_equalizer(self):
        return self.payload_equalizer

    def set_payload_equalizer(self, payload_equalizer):
        self.payload_equalizer = payload_equalizer

    def get_packet_len(self):
        return self.packet_len

    def set_packet_len(self, packet_len):
        self.packet_len = packet_len

    def get_header_formatter(self):
        return self.header_formatter

    def set_header_formatter(self, header_formatter):
        self.header_formatter = header_formatter

    def get_header_equalizer(self):
        return self.header_equalizer

    def set_header_equalizer(self, header_equalizer):
        self.header_equalizer = header_equalizer


def main(top_block_cls=send_test_rx, options=None):

    tb = top_block_cls()
    tb.start()
    try:
        raw_input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()


if __name__ == '__main__':
    main()
