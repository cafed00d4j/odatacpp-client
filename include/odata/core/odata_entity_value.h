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
 
#pragma once

#include "odata/edm/odata_edm.h"
#include "odata/core/odata_value.h"
#include "odata/core/odata_structured_value.h"

namespace odata { namespace core
{

class odata_entity_value : public odata_structured_value
{
public:
	odata_entity_value(std::shared_ptr<::odata::edm::edm_entity_type> type) : odata_structured_value(type)
	{}

    odata_entity_value(odata_property_map properties, std::shared_ptr<::odata::edm::edm_entity_type> type) : odata_structured_value(type, properties)
	{}

	ODATACPP_CLIENT_API ::utility::string_t get_entity_key_string();

private:
    ::utility::string_t to_key(std::shared_ptr<odata_primitive_value> value);
};

}}