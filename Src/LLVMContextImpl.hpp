/**
 * @file LLVMContextImpl.hpp
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

#ifndef _DILITHIUM_LLVM_CONTEXT_IMPL_HPP
#define _DILITHIUM_LLVM_CONTEXT_IMPL_HPP

#include <Dilithium/TrackingMDRef.hpp>

#include <unordered_map>
#include <unordered_set>

#include <boost/container/small_vector.hpp>


namespace Dilithium
{
	class ConstantInt;
	class ConstantFP;
	class LLVMContext;
	class Type;
	class Value;

	class MDAttachmentMap
	{
	public:
		bool empty() const
		{ 
			return attachments_.empty();
		}
		size_t size() const
		{
			return attachments_.size();
		}

		MDNode* Lookup(uint32_t id) const;

		void Set(uint32_t id, MDNode& md);

		void Erase(uint32_t id);

		void GetAll(boost::container::small_vector_base<std::pair<uint32_t, MDNode*>>& result) const;

		template <typename PredTy>
		void remove_if(PredTy should_remove)
		{
			attachments_.erase(std::remove_if(attachments_.begin(), attachments_.end(), should_remove), attachments_.end());
		}

	private:
		boost::container::small_vector<std::pair<uint32_t, TrackingMDNodeRef>, 2> attachments_;
	};

	// TODO: Consider merged with LLVMContext
	struct LLVMContextImpl
	{
		explicit LLVMContextImpl(LLVMContext& context);
		~LLVMContextImpl();

		// Metadata string to ID mapping
		std::unordered_map<std::string, uint32_t> custom_md_kind_names;

		//DILITHIUM_NOT_IMPLEMENTED;
	};
}

#endif		// _DILITHIUM_LLVM_CONTEXT_IMPL_HPP
