// The MIT License (MIT)
//
// Copyright (c) 2013-2015 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "asteroid.h"

namespace daw {
	namespace asteroid {
		ast_node::ast_node( ast_node_type node_type ): 
			m_node_type{ node_type } { }

		ast_node::ast_node_type const& ast_node::node_type() const {
			return m_node_type;
		}

		ast_node::~ast_node( ) { }

		ast_node_scope::ast_node_scope( ): 
			ast_node { ast_node::ast_node_type::scope }, 
			children { } { }

		ast_node_type_identifier::ast_node_type_identifier( std::string type_name ): 
			ast_node { ast_node::ast_node_type::type_identifier }, 
			name { std::move( type_name ) }, 
			width { 0 }, 
			components { } { }

		addressable::~addressable( ) { }

		has_value::~has_value( ) { }

		ast_node_cpu_register::ast_node_cpu_register( std::string register_name ):
			ast_node { ast_node::ast_node_type::cpu_register }, 
			name { std::move( register_name ) } { }

		ast_node_memory_address::ast_node_memory_address(uintmax_t memory_location):
			ast_node { ast_node::ast_node_type::memory_address },
			location { memory_location } { }

		assignable::~assignable( ) { }

		ast_node_variable_declaration::ast_node_variable_declaration( std::shared_ptr<ast_node_type_identifier> variable_type_id, std::string variable_name ):
			ast_node { ast_node::ast_node_type::variable_declaration },
			location{ },
			name{ std::move( variable_name ) },
			variable_type{ variable_type_id }  { }
	}	// namespace asteroid
}	// namespace daw

