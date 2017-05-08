/**
 * @file Instruction.hpp
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

#ifndef _DILITHIUM_INSTRUCTUION_HPP
#define _DILITHIUM_INSTRUCTUION_HPP

#pragma once

#include <Dilithium/User.hpp>
#include <Dilithium/Value.hpp>

namespace Dilithium
{
	class BasicBlock;

	class Instruction : public User
	{
	public:
		typedef BasicBlock ParentType;

	public:
		enum TermOps
		{
#define FIRST_TERM_INST(N)					TermOpsBegin = N,
#define HANDLE_TERM_INST(N, OPC, CLASS)		OPC = N,
#define LAST_TERM_INST(N)					TermOpsEnd = N + 1
#include "Instruction.inc"
		};

		enum BinaryOps
		{
#define FIRST_BINARY_INST(N)				BinaryOpsBegin = N,
#define HANDLE_BINARY_INST(N, OPC, CLASS)	OPC = N,
#define LAST_BINARY_INST(N)					BinaryOpsEnd = N + 1
#include "Instruction.inc"
		};

		enum MemoryOps
		{
#define FIRST_MEMORY_INST(N)				MemoryOpsBegin = N,
#define HANDLE_MEMORY_INST(N, OPC, CLASS)	OPC = N,
#define LAST_MEMORY_INST(N)					MemoryOpsEnd = N + 1
#include "Instruction.inc"
		};

		enum CastOps
		{
#define FIRST_CAST_INST(N)					CastOpsBegin = N,
#define HANDLE_CAST_INST(N, OPC, CLASS)		OPC = N,
#define LAST_CAST_INST(N)					CastOpsEnd = N + 1
#include "Instruction.inc"
		};

		enum OtherOps
		{
#define FIRST_OTHER_INST(N)					OtherOpsBegin = N,
#define HANDLE_OTHER_INST(N, OPC, CLASS)	OPC = N,
#define LAST_OTHER_INST(N)					OtherOpsEnd = N + 1
#include "Instruction.inc"
		};

	public:
		static bool classof(Value const * v)
		{
			return v->GetValueId() >= Value::InstructionVal;
		}

		// DILITHIUM_NOT_IMPLEMENTED
	};
}

#endif		// _DILITHIUM_INSTRUCTUION_HPP
