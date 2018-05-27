#pragma once

#include "gui/gui.h"
#include "gui/helpers.h"

namespace ui {
	namespace forms {

		// Control is a user interface element for manipulating a model's property
		struct Control : ui::InlineElement {
			Control();

			virtual void submit() = 0;
		};

	}
}