#pragma once

#include <vector>
#include <iostream>
#include <type_traits>

namespace svirskey
{
    template <class T, size_t size_outer, size_t size_middle = size_outer, size_t size_inner = 1>
    requires (std::is_arithmetic_v<T> && (size_outer > 0 && size_middle > 0 && size_inner > 0))
	class vector_3d;
    
	template<class T, size_t size_outer, size_t size_inner = size_outer>
    requires (std::is_arithmetic_v<T> && size_outer > 0 && size_inner > 0)
	class vector_2d
	{
    public:
        using cont_2d = std::vector<std::vector<T>>;

	protected:

		int32_t size_outer_;

        int32_t size_inner_;

		cont_2d field_;

	public:

		vector_2d(std::istream& in) : size_outer_(size_outer), size_inner_(size_inner), field_(size_outer, std::vector<T>(size_inner, T())) { scan(in); }

		vector_2d() : size_outer_(size_outer), size_inner_(size_inner), field_(size_outer, std::vector<T>(size_inner, T())) { }

        vector_2d(const vector_3d<T, size_outer, size_inner>& other) : size_outer_(size_outer), size_inner_(size_inner), field_(size_outer, std::vector<T>(size_inner, T())) 
        { 
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_inner_; ++j)
                {
                    field_[i][j] = other[i][j][0];
                }
            }
        }

        virtual ~vector_2d() = default;

        int32_t get_size_outer() const {return size_outer_;}

        int32_t get_size_inner() const {return size_inner_;}

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
                for (int32_t j = 0; j < size_inner_; ++j)
                {
                    in >> field_[i][j];
                }
            }
        }

		void print(std::ostream& out = std::cout) const
        {
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_inner_; ++j)
                {
                    out << field_[i][j] << " ";
                }
                out << std::endl;
            }
            out << std::endl;
        }

        std::vector<int32_t>& operator [] (const int32_t& index)
        {
            return field_[index];
        }

        const std::vector<int32_t>& operator [] (const int32_t& index) const
        {
            return field_[index];
        }
	};

    template <class T, size_t size_outer, size_t size_middle, size_t size_inner>
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

        vector_3d() : size_outer_(size_outer), size_middle_(size_middle), size_inner_(size_inner), 
                                        field_(size_outer, std::vector<std::vector<T>>(size_middle, std::vector<T>(size_inner, T() ))) {}

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
                    field_[i][j][0] = other[i][j];
                }
            }
        }

        virtual ~vector_3d() = default;

        int32_t get_size_outer() const {return size_outer_;}

        int32_t get_size_middle() const {return size_middle_;}

        int32_t get_size_inner() const {return size_inner_;}

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

        void print(std::ostream& out = std::cout) const
        {
            out << std::endl;
            for (int32_t i = 0; i < size_outer_; ++i)
            {
                for (int32_t j = 0; j < size_middle_; ++j)
                {
                    out << "(";
                    for (int32_t k = 0; k < field_[i][j].size(); ++k)
                    {
                        out << field_[i][j][k];
                        if (k != field_[i][j].size() - 1)
                            out << ", ";
                    }
                    out << ")\t\t";
                }
                out << std::endl;
            }
            out << std::endl;
        }

		std::vector<std::vector<int32_t>>& operator [] (const int32_t& index)
        {
            return field_[index];
        }

        const std::vector<std::vector<int32_t>>& operator [] (const int32_t& index) const
        {
            return field_[index];
        }
	};
}