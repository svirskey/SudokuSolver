#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

namespace svirskey
{
	template<class T, size_t sz_A, size_t sz_B = sz_A>
    requires (std::is_arithmetic_v<T> && sz_A > 0 && sz_B > 0)
	class vector_2d
	{
    public:
        using cont_2d = std::vector<std::vector<T>>;

	protected:

		int32_t size_A;

        int32_t size_B;

		cont_2d field;

	public:

		vector_2d(std::istream& in) : size_A(sz_A), size_B(sz_B), field(sz_A, std::vector<T>(sz_B, T())) { scan(in); }

		vector_2d() : size_A(sz_A), size_B(sz_B), field(sz_A, std::vector<T>(sz_B, T())) { }

        virtual ~vector_2d() = default;

        int32_t get_size_A() const {return size_A;}

        int32_t get_size_B() const {return size_B;}

	    void clear()
        {
            for (int32_t i = 0; i < size_A; ++i)
            {
                field[i].clear();
            }
        }

        void scan(std::istream& in)
        {
            clear();
            for (int32_t i = 0; i < size_A; ++i)
            {
                for (int32_t j = 0; j < size_B; ++j)
                {
                    in >> field[i][j];
                }
            }
        }

		void print(std::ostream& out) const
        {
            for (int32_t i = 0; i < size_A; ++i)
            {
                for (int32_t j = 0; j < size_B; ++j)
                {
                    out << field[i][j] << " ";
                }
                out << std::endl;
            }
        }
        
        template <class T_, size_t sz_A_, size_t sz_B_, size_t sz_C_>
        friend class vector_3d;
	};

    template <class T, size_t sz_A, size_t sz_B = sz_A, size_t sz_C = sz_B>
    requires (std::is_arithmetic_v<T> && (sz_A > 0 && sz_B > 0 && sz_C > 0))
	class vector_3d
	{
    public:
        using cont_3d = std::vector<std::vector<std::vector<T>>>;

	protected:

    	int32_t size_A;

        int32_t size_B;

        int32_t size_C;

        cont_3d field;

	public:

        vector_3d(std::istream& in) : size_A(sz_A), size_B(sz_B), size_C(sz_C), 
                                        field(sz_A, std::vector<std::vector<T>>(sz_B, std::vector<T>(sz_C, T() )))
        {
            for (int32_t i = 0; i < size_A; ++i)
            {
                for (int32_t j = 0; j < size_B; ++j)
                {
                    in >>  field[i][j][0];
                }
            }
        }

		vector_3d(const vector_2d<T, sz_A, sz_B>& other) :  size_A(sz_A), size_B(sz_B), size_C(sz_C), 
                                                                field(sz_A, std::vector<std::vector<T>>(sz_B, std::vector<T>(sz_C, T() )))
        {
            for (int32_t i = 0; i < size_A; ++i)
            {
                for (int32_t j = 0; j < size_B; ++j)
                {
                    field[i][j][0] = other.field[i][j];
                }
            }
        }

        virtual ~vector_3d() = default;

        int32_t get_size_A() const {return size_A;}

        int32_t get_size_B() const {return size_B;}

        int32_t get_size_C() const {return size_C;}

        void clear()
        {
            for (int32_t i = 0; i < size_A; ++i) 
            {
                for (int32_t j = 0; j < size_B; ++j)
                {
                    field[i][j].clear();
                }
            }
        }

		std::vector<std::vector<int32_t>>& operator [] (const int32_t& index)
        {
            return field[index];
        }

	};
}