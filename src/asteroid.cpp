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
		ast_node::ast_node( ast_node_type node_type ) : m_node_type{node_type} {}

		ast_node::ast_node_type const &ast_node::node_type( ) const {
			return m_node_type;
		}

		ast_node::~ast_node( ) {}

		ast_node_scope::ast_node_scope( ) : ast_node{ast_node::ast_node_type::scope}, children{} {}

		ast_node_scope::~ast_node_scope( ) {}

		ast_node_type_identifier::ast_node_type_identifier( std::string type_name )
		  : ast_node{ast_node::ast_node_type::type_identifier}, name{std::move( type_name )}, width{0}, components{} {}

		ast_node_type_identifier::~ast_node_type_identifier( ) {}

		addressable::~addressable( ) {}

		has_value::~has_value( ) {}

		ast_node_cpu_register::ast_node_cpu_register( std::string register_name )
		  : ast_node{ast_node::ast_node_type::cpu_register}, name{std::move( register_name )} {}

		ast_node_cpu_register::~ast_node_cpu_register( ) {}

		ast_node_memory_address::ast_node_memory_address( uintmax_t memory_location )
		  : ast_node{ast_node::ast_node_type::memory_address}, location{memory_location} {}

		ast_node_memory_address::~ast_node_memory_address( ) {}

		assignable::~assignable( ) {}

		ast_node_variable_declaration::ast_node_variable_declaration(
		  std::shared_ptr<ast_node_type_identifier> variable_type_id, std::string variable_name )
		  : ast_node{ast_node::ast_node_type::variable_declaration}
		  , location{}
		  , name{std::move( variable_name )}
		  , variable_type{variable_type_id} {}

		ast_node_variable_declaration::~ast_node_variable_declaration( ) {}

		ast_node_assignement::ast_node_assignement( std::shared_ptr<assignable> left, std::shared_ptr<has_value> right )
		  : ast_node{ast_node::ast_node_type::assignment}, lhs{std::move( left )}, rhs{std::move( right )} {}

		ast_node_assignement::~ast_node_assignement( ) {}

		ast_node_loop::ast_node_loop( std::shared_ptr<ast_node_scope> loop_body )
		  : ast_node{ast_node::ast_node_type::loop}, scope{std::move( loop_body )} {}

		ast_node_loop::~ast_node_loop( ) {}

		ast_node_label::ast_node_label( std::string label_name )
		  : ast_node{ast_node::ast_node_type::label}, identifier{std::move( label_name )} {}

		ast_node_label::~ast_node_label( ) {}

		ast_node_jump::ast_node_jump( std::shared_ptr<ast_node_label> destination )
		  : ast_node{ast_node::ast_node_type::jump}, label{std::move( destination )} {}

		ast_node_jump::~ast_node_jump( ) {}

		ast_node_operator_add::ast_node_operator_add( std::shared_ptr<assignable> Result, std::shared_ptr<has_value> Left,
		                                              std::shared_ptr<has_value> Right )
		  : ast_node{ast_node::ast_node_type::operator_add}
		  , result{std::move( Result )}
		  , lhs{std::move( Left )}
		  , rhs{std::move( Right )} {}

		ast_node_operator_add::~ast_node_operator_add( ) {}

		ast_node_operator_sub::ast_node_operator_sub( std::shared_ptr<assignable> Result, std::shared_ptr<has_value> Left,
		                                              std::shared_ptr<has_value> Right )
		  : ast_node{ast_node::ast_node_type::operator_sub}
		  , result{std::move( Result )}
		  , lhs{std::move( Left )}
		  , rhs{std::move( Right )} {}

		ast_node_operator_sub::~ast_node_operator_sub( ) {}

		ast_node_operator_mul::ast_node_operator_mul( std::shared_ptr<assignable> Result, std::shared_ptr<has_value> Left,
		                                              std::shared_ptr<has_value> Right )
		  : ast_node{ast_node::ast_node_type::operator_mul}
		  , result{std::move( Result )}
		  , lhs{std::move( Left )}
		  , rhs{std::move( Right )} {}

		ast_node_operator_mul::~ast_node_operator_mul( ) {}

		ast_node_operator_div::ast_node_operator_div( std::shared_ptr<assignable> Result, std::shared_ptr<has_value> Left,
		                                              std::shared_ptr<has_value> Right )
		  : ast_node{ast_node::ast_node_type::operator_div}
		  , result{std::move( Result )}
		  , lhs{std::move( Left )}
		  , rhs{std::move( Right )} {}

		ast_node_operator_div::~ast_node_operator_div( ) {}

		callable::~callable( ) {}

		ast_node_function_definition::ast_node_function_definition( std::string function_name )
		  : ast_node{ast_node::ast_node_type::function_definition}
		  , name{std::move( function_name )}
		  , arguments{}
		  , scope{} {}

		ast_node_function_definition::~ast_node_function_definition( ) {}
	} // namespace asteroid
} // namespace daw
