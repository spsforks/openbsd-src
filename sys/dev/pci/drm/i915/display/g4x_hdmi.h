/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2020 Intel Corporation
 */

#ifndef _G4X_HDMI_H_
#define _G4X_HDMI_H_

#include <linux/types.h>

#include "i915_reg_defs.h"

enum port;
#define drm_i915_private inteldrm_softc
struct drm_atomic_state;
struct drm_connector;
struct drm_i915_private;

void g4x_hdmi_init(struct drm_i915_private *dev_priv,
		   i915_reg_t hdmi_reg, enum port port);
int g4x_hdmi_connector_atomic_check(struct drm_connector *connector,
				    struct drm_atomic_state *state);

#endif
