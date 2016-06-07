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

#pragma once

#include <memory>
#include <vector>

namespace daw {
	namespace asteroid {
		struct ast_node: public std::enable_shared_from_this<ast_node> {
			enum class ast_node_type { scope, type_identifier, memory_address, cpu_register, variable_declaration, assignment, loop, label, jump,
										operator_add, operator_sub, operator_mul, operator_div };

		protected:
			ast_node_type m_node_type;
		public:
			ast_node( ast_node_type node_type );
			ast_node_type const & node_type( ) const;
			virtual ~ast_node( );

			ast_node( ) = delete;
			ast_node( ast_node const & ) = default;
			ast_node( ast_node && ) = default;
			ast_node & operator=( ast_node const & ) = default;
			ast_node & operator=( ast_node && ) = default;
			
		};	// struct ast_node

		struct ast_node_scope: public ast_node {
			ast_node_scope( );

			std::vector<std::shared_ptr<ast_node>> children;
			
			ast_node_scope( ast_node_scope const & ) = default;
			ast_node_scope( ast_node_scope && ) = default;
			ast_node_scope & operator=( ast_node_scope const & ) = default;
			ast_node_scope & operator=( ast_node_scope && ) = default;
			~ast_node_scope( ) = default;
		};	// ast_node_scope

		struct ast_node_type_identifier: public ast_node {
			std::string name;
			uintmax_t width;
			std::vector<std::shared_ptr<ast_node_type_identifier>> components;
			ast_node_type_identifier( std::string type_name );


			ast_node_type_identifier( ast_node_type_identifier const & ) = default;
			ast_node_type_identifier( ast_node_type_identifier && ) = default;
			ast_node_type_identifier & operator=( ast_node_type_identifier const & ) = default;
			ast_node_type_identifier & operator=( ast_node_type_identifier && ) = default;
			~ast_node_type_identifier( ) = default;
		};	// ast_node_type_identifier
		
		struct addressable {
			virtual ~addressable( );
		};	// struct addressable

		struct has_value {
			virtual ~has_value( );
		};	// struct assignable

		struct ast_node_cpu_register: public ast_node, public addressable, public has_value {
			std::string name;
			ast_node_cpu_register( std::string register_name );

			ast_node_cpu_register( ast_node_cpu_register const & ) = default;
			ast_node_cpu_register( ast_node_cpu_register && ) = default;
			ast_node_cpu_register & operator=( ast_node_cpu_register const & ) = default;
			ast_node_cpu_register & operator=( ast_node_cpu_register && ) = default;
			~ast_node_cpu_register( ) = default;
		};	// ast_node_cpu_register

		struct ast_node_memory_address: public ast_node, public addressable, public has_value {
			ast_node_memory_address( );
			uintmax_t location;
			ast_node_memory_address( ast_node_memory_address const & ) = default;
			ast_node_memory_address( ast_node_memory_address && ) = default;
			ast_node_memory_address & operator=( ast_node_memory_address const & ) = default;
			ast_node_memory_address & operator=( ast_node_memory_address && ) = default;
			~ast_node_memory_address( ) = default;
		};	// ast_node_memory_address

		struct assignable {
			virtual ~assignable( );
		};	// struct assignable

		struct ast_node_variable_declaration: public ast_node, public assignable, public has_value {
			ast_node_variable_declaration( ast_node_type_identifier type_identifier );
		
			std::shared_ptr<addressable> location;

			ast_node_variable_declaration( ast_node_variable_declaration const & ) = default;
			ast_node_variable_declaration( ast_node_variable_declaration && ) = default;
			ast_node_variable_declaration & operator=( ast_node_variable_declaration const & ) = default;
			ast_node_variable_declaration & operator=( ast_node_variable_declaration && ) = default;
			~ast_node_variable_declaration( ) = default;
		};	// ast_node_variable_declaration

		struct ast_node_assignement: public ast_node {
			ast_node_assignement( );
			std::weak_ptr<assignable> lhs;
			std::weak_ptr<has_value> rhs;
			ast_node_assignement( ast_node_assignement const & ) = default;
			ast_node_assignement( ast_node_assignement && ) = default;
			ast_node_assignement & operator=( ast_node_assignement const & ) = default;
			ast_node_assignement & operator=( ast_node_assignement && ) = default;
			~ast_node_assignement( ) = default;
		};	// ast_node_assignement
	
		struct ast_node_loop: public ast_node {
			ast_node_loop( );
			
			ast_node_scope scope;

			ast_node_loop( ast_node_loop const & ) = default;
			ast_node_loop( ast_node_loop && ) = default;
			ast_node_loop & operator=( ast_node_loop const & ) = default;
			ast_node_loop & operator=( ast_node_loop && ) = default;
			~ast_node_loop( ) = default;
		};	// ast_node_loop

		struct ast_node_label: public ast_node {
			ast_node_label( );
			
			std::string identifier;
			ast_node_label( ast_node_label const & ) = default;
			ast_node_label( ast_node_label && ) = default;
			ast_node_label & operator=( ast_node_label const & ) = default;
			ast_node_label & operator=( ast_node_label && ) = default;
			~ast_node_label( ) = default;
		};	// ast_node_label

		struct ast_node_jump: public ast_node {
			ast_node_jump( );
			
			std::shared_ptr<ast_node_label> label;
			ast_node_jump( ast_node_jump const & ) = default;
			ast_node_jump( ast_node_jump && ) = default;
			ast_node_jump & operator=( ast_node_jump const & ) = default;
			ast_node_jump & operator=( ast_node_jump && ) = default;
			~ast_node_jump( ) = default;
		};	// ast_node_jump

		struct ast_node_operator_add: public ast_node {
			ast_node_operator_add( );
			std::shared_ptr<assignable> result;
			std::shared_ptr<has_value> lhs;
			std::shared_ptr<has_value> rhs;
			ast_node_operator_add( ast_node_operator_add const & ) = default;
			ast_node_operator_add( ast_node_operator_add && ) = default;
			ast_node_operator_add & operator=( ast_node_operator_add const & ) = default;
			ast_node_operator_add & operator=( ast_node_operator_add && ) = default;
			~ast_node_operator_add( ) = default;
		};	// ast_node_operator_add

		struct ast_node_operator_sub: public ast_node {
			ast_node_operator_sub( );
			std::shared_ptr<assignable> result;
			std::shared_ptr<has_value> lhs;
			std::shared_ptr<has_value> rhs;
			ast_node_operator_sub( ast_node_operator_sub const & ) = default;
			ast_node_operator_sub( ast_node_operator_sub && ) = default;
			ast_node_operator_sub & operator=( ast_node_operator_sub const & ) = default;
			ast_node_operator_sub & operator=( ast_node_operator_sub && ) = default;
			~ast_node_operator_sub( ) = default;
		};	// ast_node_operator_sub

		struct ast_node_operator_mul: public ast_node {
			ast_node_operator_mul( );
			std::shared_ptr<assignable> result;
			std::shared_ptr<has_value> lhs;
			std::shared_ptr<has_value> rhs;
			ast_node_operator_mul( ast_node_operator_mul const & ) = default;
			ast_node_operator_mul( ast_node_operator_mul && ) = default;
			ast_node_operator_mul & operator=( ast_node_operator_mul const & ) = default;
			ast_node_operator_mul & operator=( ast_node_operator_mul && ) = default;
			~ast_node_operator_mul( ) = default;
		};	// ast_node_operator_mul

		struct ast_node_operator_div: public ast_node {
			ast_node_operator_div( );
			std::shared_ptr<assignable> result;
			std::shared_ptr<has_value> lhs;
			std::shared_ptr<has_value> rhs;
			ast_node_operator_div( ast_node_operator_div const & ) = default;
			ast_node_operator_div( ast_node_operator_div && ) = default;
			ast_node_operator_div & operator=( ast_node_operator_div const & ) = default;
			ast_node_operator_div & operator=( ast_node_operator_div && ) = default;
			~ast_node_operator_div( ) = default;
		};	// ast_node_operator_div








	}	// namespace asteroid
}	// namespace daw

