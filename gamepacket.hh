#ifndef __GAMEPACKET_HPP__
#define __GAMEPACKET_HPP__
#include <string>
#include <memory>
#include <vector>
#include <variant>
#include <cstring>
#include <cstddef>
#include <initializer_list>
namespace KHPS
{
	namespace utils
	{
		struct vector2_f {
		public:
			float m_x;
			float m_y;
		};

		struct vector3_f {
		public:
			float m_x;
			float m_y;
			float m_z;
		};

		enum : uint8_t {
			INT = 0,
			UINT,
			FLOAT,
			VECTOR2F,
			VECTOR3F,
			STRING
		};
	}

	namespace types
	{
		using variant = std::variant<
			int,
			unsigned int,
			float,
			utils::vector2_f,
			utils::vector3_f,
			std::string>;
		using initializer = std::initializer_list<variant>;
	}

	class gamepacket_t {
	public:
		gamepacket_t()
			= default;
		~gamepacket_t()
		{
			delete[] m_data;
			m_len = 0, m_pos = 0;
		}
		gamepacket_t(const types::initializer& container)
		{
			m_len = 61;
			std::memset(m_data, 0, 61);
			std::memcpy(m_data, &m_type, sizeof(int));
			std::memcpy(m_data + 4, &m_packet, sizeof(int));
			std::memcpy(m_data + 8, &m_net_id, sizeof(int));
			std::memcpy(m_data + 16, &m_state, sizeof(int));
			std::memcpy(m_data + 24, &m_delay, sizeof(int));
			// deserialize from intializer parameter
			std::vector<types::variant> t_(container);
			for (int i = 0; i < t_.size(); i++) {
				const types::variant& var = t_[i];
				switch (var.index()) {
				case utils::INT: {
					int sum = std::get<int>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x9;
					std::memcpy(blc + m_len + 2, &sum, sizeof(int));
					m_len += 6;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::FLOAT: {
					float sum = std::get<float>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x1;
					std::memcpy(blc + m_len + 2, &sum, sizeof(float));
					m_len += 6;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::UINT: {
					unsigned int sum = std::get<unsigned int>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x5;
					std::memcpy(blc + m_len + 2, &sum, sizeof(int));
					m_len += 6;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::VECTOR2F: {
					utils::vector2_f sum = std::get<utils::vector2_f>(var);
					uint8_t* blc = new uint8_t[m_len + 0xA];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x3;
					std::memcpy(blc + m_len + 2, &sum.m_x, sizeof(float));
					std::memcpy(blc + m_len + 6, &sum.m_y, sizeof(float));
					m_len += 0xA;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::VECTOR3F: {
					utils::vector3_f sum = std::get<utils::vector3_f>(var);
					uint8_t* blc = new uint8_t[m_len + 14];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x4;
					std::memcpy(blc + m_len + 2, &sum.m_x, sizeof(float));
					std::memcpy(blc + m_len + 6, &sum.m_y, sizeof(float));
					std::memcpy(blc + m_len + 10, &sum.m_z, sizeof(float));
					m_len += 14;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::STRING: {
					std::string str = std::get<std::string>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6 + str.length()];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = sizeof(uint16_t);
					int lens = (int)str.length();
					std::memcpy(blc + m_len + 2, &lens, 4);
					std::memcpy(blc + m_len + 6, str.data(), lens);
					m_len += 6 + lens;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} default:
					break;
				}
			}
		}
		gamepacket_t& operator= (const types::initializer& container)
		{
			m_len = 61;
			std::memset(m_data, 0, 61);
			std::memcpy(m_data, &m_type, sizeof(int));
			std::memcpy(m_data + 4, &m_packet, sizeof(int));
			std::memcpy(m_data + 8, &m_net_id, sizeof(int));
			std::memcpy(m_data + 16, &m_state, sizeof(int));
			std::memcpy(m_data + 24, &m_delay, sizeof(int));
			// deserialize from intializer parameter
			std::vector<types::variant> t_(container);
			for (int i = 0; i < t_.size(); i++) {
				const types::variant& var = t_[i];
				switch (var.index()) {
				case utils::INT: {
					int sum = std::get<int>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x9;
					std::memcpy(blc + m_len + 2, &sum, sizeof(int));
					m_len += 6;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::FLOAT: {
					float sum = std::get<float>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x1;
					std::memcpy(blc + m_len + 2, &sum, sizeof(float));
					m_len += 6;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::UINT: {
					unsigned int sum = std::get<unsigned int>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x5;
					std::memcpy(blc + m_len + 2, &sum, sizeof(int));
					m_len += 6;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::VECTOR2F: {
					utils::vector2_f sum = std::get<utils::vector2_f>(var);
					uint8_t* blc = new uint8_t[m_len + 0xA];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x3;
					std::memcpy(blc + m_len + 2, &sum.m_x, sizeof(float));
					std::memcpy(blc + m_len + 6, &sum.m_y, sizeof(float));
					m_len += 0xA;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::VECTOR3F: {
					utils::vector3_f sum = std::get<utils::vector3_f>(var);
					uint8_t* blc = new uint8_t[m_len + 14];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = 0x4;
					std::memcpy(blc + m_len + 2, &sum.m_x, sizeof(float));
					std::memcpy(blc + m_len + 6, &sum.m_y, sizeof(float));
					std::memcpy(blc + m_len + 10, &sum.m_z, sizeof(float));
					m_len += 14;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} case utils::STRING: {
					std::string str = std::get<std::string>(var);
					uint8_t* blc = new uint8_t[m_len + 0x6 + str.length()];
					std::memcpy(blc, m_data, m_len);
					delete[] m_data;
					m_data = blc;
					blc[m_len] = m_pos;
					blc[m_len + 1] = sizeof(uint16_t);
					int lens = (int)str.length();
					std::memcpy(blc + m_len + 2, &lens, 4);
					std::memcpy(blc + m_len + 6, str.data(), lens);
					m_len += 6 + lens;
					m_pos++;
					m_data[60] = m_pos;
					break;
				} default:
					break;
				}
			}
		}
		constexpr uint8_t* get()
		{
			return m_data;
		}
		constexpr uint32_t lens()
		{
			return m_len;
		}
	private:
		uint32_t m_pos;
		uint32_t m_len;
	private:
		int m_type = 0x4;
		int m_packet = 0x1;
		int m_state = 0x8;
	public:
		int m_net_id = -1;
		int m_delay = -1;
	private:
		uint8_t* m_data = new uint8_t[61];
	};
}
#endif // !__GAMEPACKET_HPP__
