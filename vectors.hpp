#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

namespace svirskey
{
	template<class T, size_t size_outer, size_t size_middle = size_outer>
    requires (std::is_arithmetic_v<T> && size_outer > 0 && size_middle > 0)
	class vector_2d
	{
    public:
        using cont_2d = std::vector<std::vector<T>>;

	protected:

		int32_t size_outer_;

        int32_t size_middle_;

		cont_2d field_;

	public:

		vector_2d(std::istream& in) : size_outer_(size_outer), size_middle_(size_middle), field_(size_outer, std::vector<T>(size_middle, T())) { scan(in); }

		vector_2d() : size_outer_(size_outer), size_middle_(size_middle), field_(size_outer, std::vector<T>(size_middle, T())) { }

        virtual ~vector_2d() = default;

        int32_t get_size_outer_() const {return size_outer_;}

        int32_t get_size_middle_() const {return size_middle_;}

	    void clear()
        {
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                field_[i].clear();
            }
        }

        void scan(std::istream& in)
        {
            clear();
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_middle_; ++j)
                {
                    in >> field_[i][j];
                }
            }
        }

		void print(std::ostream& out) const
        {
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_middle_; ++j)
                {
                    out << field_[i][j] << " ";
                }
                out << std::endl;
            }
        }

        std::vector<int32_t>& operator [] (const int32_t& index)
        {
            return field_[index];
        }

        template <class T_, size_t size_outer_, size_t size_middle_, size_t size_inner_>
        friend class vector_3d;
	};

    template <class T, size_t size_outer, size_t size_middle = size_outer, size_t size_inner = size_middle>
    requires (std::is_arithmetic_v<T> && (size_outer > 0 && size_middle > 0 && size_inner > 0))
	class vector_3d
	{
    public:
        using cont_3d = std::vector<std::vector<std::vector<T>>>;

	protected:

    	int32_t size_outer_;

        int32_t size_middle_;

        int32_t size_inner_;

        cont_3d field_;

	public:

        vector_3d(std::istream& in) : size_outer_(size_outer), size_middle_(size_middle), size_inner_(size_inner), 
                                        field_(size_outer, std::vector<std::vector<T>>(size_middle, std::vector<T>(size_inner, T() )))
        {
            
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_middle_; ++j)
                {
                    in >>  field_[i][j][0];
                }
            }
        }

		vector_3d(const vector_2d<T, size_outer, size_middle>& other) :  size_outer_(size_outer), size_middle_(size_middle), size_inner_(size_inner), 
                                                                field_(size_outer, std::vector<std::vector<T>>(size_middle, std::vector<T>(size_inner, T() )))
        {
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_middle_; ++j)
                {
                    field_[i][j][0] = other.field_[i][j];
                }
            }
        }

        virtual ~vector_3d() = default;

        int32_t get_size_outer_() const {return size_outer_;}

        int32_t get_size_middle_() const {return size_middle_;}

        int32_t get_size_inner_() const {return size_inner_;}

        void clear()
        {
            for (int32_t i = 0; i < size_outer_; ++i) 
            {
                for (int32_t j = 0; j < size_middle_; ++j)
                {
                    field_[i][j].clear();
                }
            }
        }

		std::vector<std::vector<int32_t>>& operator [] (const int32_t& index)
        {
            return field_[index];
        }

	};
}