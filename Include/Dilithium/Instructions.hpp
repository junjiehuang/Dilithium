/**
 * @file Instructions.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of Dilithium
 * For the latest info, see https://github.com/gongminmin/Dilithium
 *
 * @section LICENSE
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Minmin Gong. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _DILITHIUM_INSTRUCTUIONS_HPP
#define _DILITHIUM_INSTRUCTUIONS_HPP

#pragma once

#include <Dilithium/CXX17/string_view.hpp>
#include <Dilithium/ArrayRef.hpp>
#include <Dilithium/Attributes.hpp>
#include <Dilithium/CallingConv.hpp>
#include <Dilithium/InstrTypes.hpp>

namespace Dilithium
{
	class BasicBlock;
	class FunctionType;
	class LLVMContext;
	class Value;

	class ReturnInst;
	class CallInst;

	template <>
	struct OperandTraits<ReturnInst> : public VariadicOperandTraits<ReturnInst>
	{
	};

	template <>
	struct OperandTraits<CallInst> : public VariadicOperandTraits<CallInst>
	{
	};

	class ReturnInst : public TerminatorInst
	{
	public:
		~ReturnInst() override;

		static ReturnInst* Create(LLVMContext& context, Value* ret_val = nullptr, Instruction* insert_before = nullptr);
		static ReturnInst* Create(LLVMContext& context, Value* ret_val, BasicBlock* insert_at_end);
		static ReturnInst* Create(LLVMContext& context, BasicBlock* insert_at_end);

		Value* ReturnValue() const
		{
			return this->NumOperands() != 0 ? this->Operand(0) : nullptr;
		}

	private:
		explicit ReturnInst(LLVMContext& context, Value* ret_val = nullptr, Instruction* insert_before = nullptr);
		ReturnInst(LLVMContext& context, Value* ret_val, BasicBlock* insert_at_end);
		explicit ReturnInst(LLVMContext& context, BasicBlock* insert_at_end);
		ReturnInst(ReturnInst const & rhs);

		DEFINE_TRANSPARENT_OPERAND_ACCESSORS(ReturnInst, Value)

		// DILITHIUM_NOT_IMPLEMENTED
	};

	class CallInst : public Instruction
	{
	public:
		enum TailCallKind
		{
			TCK_None = 0,
			TCK_Tail = 1,
			TCK_MustTail = 2
		};

	public:
		~CallInst() override;

		static CallInst* Create(Value* func, ArrayRef<Value*> args, std::string_view name = "", Instruction* insert_before = nullptr);
		static CallInst* Create(FunctionType* ty, Value* func, ArrayRef<Value*> args, std::string_view name = "",
			Instruction* insert_before = nullptr);
		static CallInst* Create(Value* func, ArrayRef<Value*> args, std::string_view name, BasicBlock* insert_at_end);
		static CallInst* Create(Value* func, std::string_view name = "", Instruction* insert_before = nullptr);
		static CallInst* Create(Value* func, std::string_view name, BasicBlock* insert_at_end);

		TailCallKind GetTailCallKind() const;
		void SetTailCallKind(TailCallKind tck);

		CallingConv::ID GetCallingConv() const;
		void SetCallingConv(CallingConv::ID cc);

		AttributeSet const & GetAttributes() const
		{
			return attr_list_;
		}
		void SetAttributes(AttributeSet const & attrs)
		{
			attr_list_ = attrs;
		}

		DEFINE_TRANSPARENT_OPERAND_ACCESSORS(CallInst, Value)

	private:
		CallInst(FunctionType* ty, Value* func, ArrayRef<Value*> args, std::string_view name, Instruction* insert_before);
		CallInst(Value* func, ArrayRef<Value*> args, std::string_view name, Instruction* insert_before);
		CallInst(Value* func, ArrayRef<Value*> args, std::string_view name, BasicBlock* insert_at_end);
		CallInst(Value* func, std::string_view name, Instruction* insert_before);
		CallInst(Value* func, std::string_view name, BasicBlock* insert_at_end);
		CallInst(CallInst const & rhs);

		void Init(Value* func, ArrayRef<Value*> args, std::string_view name);
		void Init(FunctionType* fty, Value* func, ArrayRef<Value*> args, std::string_view name);
		void Init(Value* func, std::string_view name);

	private:
		AttributeSet attr_list_;
		FunctionType* fty_;

		// DILITHIUM_NOT_IMPLEMENTED
	};
}

#endif		// _DILITHIUM_INSTRUCTUIONS_HPP
