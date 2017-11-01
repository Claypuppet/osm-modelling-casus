/*
 * Menu.h
 *
 *  Created on: 1 Nov 2017
 *      Author: Vuurvlieg
 */

#ifndef CUI_MENU_H_
#define CUI_MENU_H_

#include "Core.h"
#include <memory>


namespace cui
{
	enum class ItemOptions {
		kItemOptionSelectable = O_SELECTABLE,
	};

	class MenuItem
	{
		typedef std::shared_ptr<ITEM> ITEMPtr;
	public:
		MenuItem(const std::string& name, const std::string& desc, ItemOptions options = ItemOptions::kItemOptionSelectable)
		: mItem(ITEMPtr(::new_item(name.c_str(), desc.c_str()), [](ITEM* item){
			::free_item(item);
		}))
		{
			::set_item_userptr(mItem.get(), this);
			setOptions(options);
		}

		MenuItem& addOption(ItemOptions options) {
			::item_opts_on(mItem.get(), static_cast<Item_Options>(options));
			return *this;
		}

		MenuItem& delOption(ItemOptions options) {
			::item_opts_off(mItem.get(), static_cast<Item_Options>(options));
			return *this;
		}

		MenuItem& setOptions(ItemOptions options) {
			::set_item_opts(mItem.get(), static_cast<Item_Options>(options));
			return *this;
		}

		ItemOptions getOptions() {
			return static_cast<ItemOptions>(::item_opts(mItem.get()));
		}

		bool isVisible() {
			return ::item_visible(mItem.get());
		}

		bool setValue(bool value) {
			return noError(::set_item_value(mItem.get(), value));
		}

		bool getValue() {
			return ::item_value(mItem.get());
		}


	private:
		ITEMPtr mItem;
	};

	class Menu
	{
	public:
		Menu();
		~Menu();
	};

} /* namespace cui */

#endif /* CUI_MENU_H_ */
