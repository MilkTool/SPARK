//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2010 - Julien Fryer - julienfryer@gmail.com				//
//																				//
// This software is provided 'as-is', without any express or implied			//
// warranty.  In no event will the authors be held liable for any damages		//
// arising from the use of this software.										//
//																				//
// Permission is granted to anyone to use this software for any purpose,		//
// including commercial applications, and to alter it and redistribute it		//
// freely, subject to the following restrictions:								//
//																				//
// 1. The origin of this software must not be misrepresented; you must not		//
//    claim that you wrote the original software. If you use this software		//
//    in a product, an acknowledgment in the product documentation would be		//
//    appreciated but is not required.											//
// 2. Altered source versions must be plainly marked as such, and must not be	//
//    misrepresented as being the original software.							//
// 3. This notice may not be removed or altered from any source distribution.	//
//////////////////////////////////////////////////////////////////////////////////

#ifndef H_SPK_SIMPLEINTERPOLATOR
#define H_SPK_SIMPLEINTERPOLATOR

#include "Core/SPK_Interpolator.h"

namespace SPK
{	
	template<typename T>
	class SimpleInterpolator : public Interpolator<T>
	{
	SPK_IMPLEMENT_REGISTERABLE(SimpleInterpolator<T>);

	public :

		static inline SimpleInterpolator<T>* create(const T& birthValue,const T& deathValue);

		inline void setValues(const T& min,const T& max);
		inline const T& getBirthValue() const;
		inline const T& getDeathValue() const;

	private :
		
		T birthValue;
		T deathValue;

		SimpleInterpolator<T>(const T& birthValue,const T& deathValue);

		virtual void interpolate(T* data,Group& group,DataSet* dataSet) const;
		virtual inline void init(T& data,Particle& particle,DataSet* dataSet) const;
	};

	typedef SimpleInterpolator<Color> ColorSimpleInterpolator;
	typedef SimpleInterpolator<float> FloatSimpleInterpolator;

	template<typename T>
	SimpleInterpolator<T>::SimpleInterpolator(const T& birthValue,const T& deathValue) :
		Interpolator(false),
		birthValue(birthValue),
		deathValue(deathValue)
	{}

	template<typename T>
	inline SimpleInterpolator<T>* SimpleInterpolator<T>::create(const T& birthValue,const T& deathValue)
	{
		return new SimpleInterpolator<T>(birthValue,deathValue);
	}

	template<typename T>
	inline void SimpleInterpolator<T>::setValues(const T& birthValue,const T& deathValue)
	{
		this->birthValue = birthValue;
		this->deathValue = deathValue;
	}

	template<typename T>
	inline const T& SimpleInterpolator<T>::getBirthValue() const
	{
		return birthValue;
	}

	template<typename T>
	inline const T& SimpleInterpolator<T>::getDeathValue() const
	{
		return deathValue;
	}

	template<typename T>
	inline void SimpleInterpolator<T>::init(T& data,Particle& particle,DataSet* dataSet) const
	{
		data = birthValue;
	}

	template<typename T>
	void SimpleInterpolator<T>::interpolate(T* data,Group& group,DataSet* dataSet) const
	{
		for (GroupIterator particleIt(group); !particleIt.end(); ++particleIt)
			interpolateParam(data[particleIt->getIndex()],deathValue,birthValue,particleIt->getEnergy());
	}
}

#endif