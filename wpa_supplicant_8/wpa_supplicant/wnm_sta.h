/*
 * IEEE 802.11v WNM related functions and structures
 * Copyright (c) 2011-2012, Qualcomm Atheros, Inc.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef WNM_STA_H
#define WNM_STA_H

struct measurement_pilot {
	u8 measurement_pilot;
	u8 subelem_len;
	u8 subelems[255];
};

struct multiple_bssid {
	u8 max_bssid_indicator;
	u8 subelem_len;
	u8 subelems[255];
};

struct neighbor_report {
	u8 bssid[ETH_ALEN];
	u32 bssid_info;
	u8 regulatory_class;
	u8 channel_number;
	u8 phy_type;
	u8 preference; /* valid if preference_present=1 */
	u16 tsf_offset; /* valid if tsf_present=1 */
	u16 beacon_int; /* valid if tsf_present=1 */
	char country[2]; /* valid if country_present=1 */
	u8 rm_capab[5]; /* valid if rm_capab_present=1 */
	u16 bearing; /* valid if bearing_present=1 */
	u16 rel_height; /* valid if bearing_present=1 */
	u32 distance; /* valid if bearing_present=1 */
	u64 bss_term_tsf; /* valid if bss_term_present=1 */
	u16 bss_term_dur; /* valid if bss_term_present=1 */
	unsigned int preference_present:1;
	unsigned int tsf_present:1;
	unsigned int country_present:1;
	unsigned int rm_capab_present:1;
	unsigned int bearing_present:1;
	unsigned int bss_term_present:1;
	struct measurement_pilot *meas_pilot;
	struct multiple_bssid *mul_bssid;
	int freq;
};


int ieee802_11_send_wnmsleep_req(struct wpa_supplicant *wpa_s,
				 u8 action, u16 intval, struct wpabuf *tfs_req);

void ieee802_11_rx_wnm_action(struct wpa_supplicant *wpa_s,
			      const struct ieee80211_mgmt *mgmt, size_t len);

int wnm_send_bss_transition_mgmt_query(struct wpa_supplicant *wpa_s,
				       u8 query_reason);
void wnm_deallocate_memory(struct wpa_supplicant *wpa_s);

int ieee802_11_send_wnmtfs_req(struct wpa_supplicant *wpa_s, struct wpabuf *tfs_req);

int ieee802_11_send_wnmdms_req(struct wpa_supplicant *wpa_s, struct wpabuf *dms_req);

#ifdef CONFIG_WNM

int wnm_scan_process(struct wpa_supplicant *wpa_s, int reply_on_fail);

#else /* CONFIG_WNM */

static inline int wnm_scan_process(struct wpa_supplicant *wpa_s,
				   int reply_on_fail)
{
	return 0;
}

#endif /* CONFIG_WNM */

#endif /* WNM_STA_H */
