/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "odata/core/odata_entity_value.h"
#include "odata/edm/edm_model_utility.h"

using namespace ::odata::edm;
using namespace ::web;

namespace odata { namespace core
{

::utility::string_t odata_entity_value::get_entity_key_string()
{
	::utility::string_t key;

	auto entitytype = std::dynamic_pointer_cast<edm_entity_type>(get_value_type());

	if (entitytype)
	{
		key += U("(");

		std::vector<::utility::string_t> key_property_names = entitytype->get_key_with_parents();
		for (size_t i = 0; i < key_property_names.size(); i++)
		{
			std::shared_ptr<odata_value> property_value;
			get_property_value(key_property_names[i], property_value);
			if (property_value)
			{
				auto property_type = property_value->get_value_type();
				if (property_type && property_type->get_type_kind() == edm_type_kind_t::Primitive)
				{
					if (i != 0)
					{
						key += U(",");
					}

					auto primitive_property_value = std::dynamic_pointer_cast<odata_primitive_value>(property_value);
					if (primitive_property_value)
					{				   
						if (key_property_names.size() == 1)
						{
                            key += to_key(primitive_property_value);
						}
						else
						{
                            key += key_property_names[i] + U("=") + to_key(primitive_property_value);
						}
					}
				}
				else
				{
					throw std::runtime_error("entity key type error!"); 
				}
			}
		}

		key += U(")");
	}

	return key;
}

::utility::string_t odata_entity_value::to_key(std::shared_ptr<odata_primitive_value> value)
{
    if (value->get_primitive_type()->get_primitive_kind() == edm_primitive_type_kind_t::String)
    {
        return U("'") + value->to_string() + U("'"); 
    }
    else
    {
        return value->to_string(); 
    }
}

}}