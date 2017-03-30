#ifndef _MYSQLCPP_UTILS_H
#define _MYSQLCPP_UTILS_H

#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include "Types.h"

namespace mysqlcpp {

namespace util {

	template <typename T, typename... Args>
	inline
		std::unique_ptr<T> make_unique(Args&&... args)
	{
		return std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
	}

	class Tokenizer
	{
	public:
		typedef std::vector<char const*> StorageType;
		typedef StorageType::size_type size_type;
		typedef StorageType::const_iterator const_iterator;
		typedef StorageType::reference reference;
		typedef StorageType::const_reference const_reference;
	public:
		Tokenizer(const std::string &src, char sep);
		~Tokenizer() = default;

		const_iterator begin() const { return m_storage.begin(); }
		const_iterator end() const { return m_storage.end(); }

		bool empty() const { return m_storage.empty(); }
		size_type size() const { return m_storage.size(); }
		reference operator [] (size_type i) { return m_storage[i]; }
		const_reference operator [] (size_type i) const { return m_storage[i]; }
	private:
		std::vector<char> m_str;
		StorageType m_storage;
	};

	template <typename T>
	struct Convert
	{
		static T convert(const std::vector<uint8>& binary)
		{
			T val{};
			if (binary.empty())
				return val;
			std::memcpy(&val, binary.data(), sizeof(val));
			return val;
		}
	};

	template <>
	struct Convert<std::string>
	{
		static std::string convert(const std::vector<uint8>& binary)
		{
			if (binary.empty())
				return{};
			const char* p = (const char*)binary.data();
			return std::string{ p, p + binary.size() };
		}
	};

}
}

#endif
