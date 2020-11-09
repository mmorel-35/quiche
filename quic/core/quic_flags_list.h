// Copyright (c) 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by the QUICHE Copybara export script.

QUIC_FLAG(FLAGS_quic_reloadable_flag_http2_use_fast_huffman_encoder, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_abort_qpack_on_stream_close, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_ack_delay_alarm_granularity, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_add_stream_info_to_idle_close_detail, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_allow_client_enabled_bbr_v2, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_avoid_too_low_probe_bw_cwnd, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_fewer_startup_round_trips, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_no_exit_startup_on_loss_with_bw_growth, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_startup_loss_exit_use_max_delivered, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_support_max_bootstrap_cwnd, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_use_post_inflight_to_detect_queuing, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_bbr2_use_tcp_inflight_hi_headroom, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_can_send_ack_frequency, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_check_keys_before_writing, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_clean_up_spdy_session_destructor, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_close_connection_in_on_can_write_with_blocked_writer, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_connection_set_initial_self_address, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_conservative_bursts, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_conservative_cwnd_and_pacing_gains, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_copy_bbr_cwnd_to_bbr2, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_deallocate_message_right_after_sent, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_default_enable_5rto_blackhole_detection2, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_default_on_pto, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_default_to_2_rttvar, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_default_to_bbr, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_default_to_bbr_v2, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_delay_initial_ack, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_server_blackhole_detection, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_draft_27, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_draft_29, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_q043, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_q046, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_q050, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_t050, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_disable_version_t051, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_discard_initial_packet_with_key_dropped, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_do_not_clip_received_error_code, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_donot_reset_ideal_next_packet_send_time, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_enable_aead_limits, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_enable_mtu_discovery_at_server, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_encrypted_control_frames, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_extract_x509_subject_using_certificate_view, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_address_validation, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_arm_pto_for_application_data, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_http3_goaway_stream_id, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_missing_initial_keys2, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_out_of_order_sending2, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_pto_pending_timer_count, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_undecryptable_packets2, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_fix_willing_and_able_to_write2, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_give_sent_packet_to_debug_visitor_after_sent, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_granular_qpack_error_codes, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_key_update_supported, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_let_connection_handle_pings, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_process_undecryptable_packets_after_async_decrypt_callback, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_record_received_min_ack_delay, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_reject_spdy_frames, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_reject_spdy_settings, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_require_handshake_confirmation, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_send_goaway_with_connection_close, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_send_path_response, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_send_timestamps, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_send_version_negotiation_for_short_connection_ids, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_split_up_send_rst, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_start_peer_migration_earlier, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_stop_sending_uses_ietf_error_code, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_testonly_default_false, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_testonly_default_true, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_unified_iw_options, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_use_circular_deque_for_unacked_packets, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_use_encryption_level_context, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_use_fast_huffman_encoder, true)
QUIC_FLAG(FLAGS_quic_reloadable_flag_quic_use_write_or_buffer_data_at_level, false)
QUIC_FLAG(FLAGS_quic_reloadable_flag_send_quic_fallback_server_config_on_leto_error, false)
QUIC_FLAG(FLAGS_quic_restart_flag_dont_fetch_quic_private_keys_from_leto, false)
QUIC_FLAG(FLAGS_quic_restart_flag_quic_enable_zero_rtt_for_tls_v2, true)
QUIC_FLAG(FLAGS_quic_restart_flag_quic_offload_pacing_to_usps2, false)
QUIC_FLAG(FLAGS_quic_restart_flag_quic_session_tickets_always_enabled, false)
QUIC_FLAG(FLAGS_quic_restart_flag_quic_support_release_time_for_gso, false)
QUIC_FLAG(FLAGS_quic_restart_flag_quic_testonly_default_false, false)
QUIC_FLAG(FLAGS_quic_restart_flag_quic_testonly_default_true, true)
