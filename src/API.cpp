/* Copyright (C) Teemu Suutari */

#include "ancient.hpp"
#include "Decompressor.hpp"
#include "common/Buffer.hpp"
#include "common/StaticBuffer.hpp"
#include "common/WrappedVectorBuffer.hpp"

namespace ancient
{

inline namespace APIv2
{

Error::Error() noexcept
{
	// nothing needed
}

Error::~Error()
{
	// nothing needed
}

InvalidFormatError::InvalidFormatError() noexcept
{
	// nothing needed
}

InvalidFormatError::~InvalidFormatError()
{
	// nothing needed
}

DecompressionError::DecompressionError() noexcept
{
	// nothing needed
}

DecompressionError::~DecompressionError()
{
	// nothing needed
}

VerificationError::VerificationError() noexcept
{
	// nothing needed
}

VerificationError::~VerificationError()
{
	// nothing needed
}

// ---


bool Decompressor::detect(const std::vector<uint8_t> &packedData) noexcept
{
	return internal::Decompressor::detect(internal::ConstStaticBuffer(packedData.data(), packedData.size()));
}

bool Decompressor::detect(const uint8_t *packedData, size_t packedSize) noexcept
{
	return internal::Decompressor::detect(internal::ConstStaticBuffer(packedData, packedSize));
}

Decompressor::Decompressor(const std::vector<uint8_t> &packedData,bool exactSizeKnown,bool verify) :
	m_impl(internal::Decompressor::create(internal::ConstStaticBuffer(packedData.data(), packedData.size()), exactSizeKnown, verify))
{
	return;
}

Decompressor::Decompressor(const uint8_t *packedData,size_t packedSize,bool exactSizeKnown,bool verify) :
	m_impl(internal::Decompressor::create(internal::ConstStaticBuffer(packedData, packedSize), exactSizeKnown, verify))
{
	return;
}

const std::string &Decompressor::getName() const noexcept
{
	return m_impl->getName();
}

size_t Decompressor::getMaxPackedSize() noexcept
{
	return internal::Decompressor::getMaxPackedSize();
}

size_t Decompressor::getMaxRawSize() noexcept
{
	return internal::Decompressor::getMaxRawSize();
}

size_t Decompressor::getPackedSize() const noexcept
{
	return m_impl->getPackedSize();
}

size_t Decompressor::getRawSize() const noexcept
{
	return m_impl->getRawSize();
}

size_t Decompressor::getImageSize() const noexcept
{
	return m_impl->getImageSize();
}
size_t Decompressor::getImageOffset() const noexcept
{
	return m_impl->getImageOffset();
}

void Decompressor::decompress(std::vector<uint8_t> &rawData,bool verify)
{
	internal::WrappedVectorBuffer buffer(rawData);
	return m_impl->decompress(buffer, verify);
}

Decompressor::~Decompressor()
{
	// nothing needed
}

}

}
