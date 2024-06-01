#pragma once

#include "ui/panels/ipanel.h"

namespace transcriby::ui {
	class TranscribePanel : public IPanel {
	public:
		TranscribePanel();
		void on_render() override;
	};
}

