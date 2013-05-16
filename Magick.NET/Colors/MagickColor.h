//=================================================================================================
// Copyright 2013 Dirk Lemstra <http://magick.codeplex.com/>
//
// Licensed under the ImageMagick License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
//
//   http://www.imagemagick.org/script/license.php
//
// Unless required by applicable law or agreed to in writing, software distributed under the
// License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied. See the License for the specific language governing permissions and
// limitations under the License.
//=================================================================================================
#pragma once

using namespace System::Drawing;

namespace ImageMagick
{
	///=============================================================================================
	///<summary>
	/// Class that represents a color.
	///</summary>
	public ref class MagickColor sealed : IEquatable<MagickColor^>, IComparable<MagickColor^>
	{
		//===========================================================================================
	private:
		//===========================================================================================
		Magick::Quantum _Red;
		Magick::Quantum _Green;
		Magick::Quantum _Blue;
		Magick::Quantum _Alpha;
		//===========================================================================================
	internal:
		//===========================================================================================
		MagickColor(MagickColor^ color);
		//===========================================================================================
		MagickColor(Magick::Color color);
		//===========================================================================================
		void Initialize(Color color);
		//===========================================================================================
		Magick::Color* CreateColor();
		//===========================================================================================
	public:
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickColor class.
		///</summary>
		MagickColor();
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickColor class using the specified color.
		///</summary>
		///<param name="color">The color to use.</param>
		MagickColor(Color color);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickColor class.
		///</summary>
		///<param name="red">Red component value of this color.</param>
		///<param name="green">Green component value of this color.</param>
		///<param name="blue">Blue component value of this color.</param>
		MagickColor(Magick::Quantum red, Magick::Quantum green, Magick::Quantum blue);
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickColor class.
		///</summary>
		///<param name="red">Red component value of this color.</param>
		///<param name="green">Green component value of this color.</param>
		///<param name="blue">Blue component value of this color.</param>
		///<param name="alpha">Alpha component value of this color.</param>
		MagickColor(Magick::Quantum red, Magick::Quantum green, Magick::Quantum blue,
			Magick::Quantum alpha);
		///==========================================================================================
		///<summary>
		/// Alpha component value of this color.
		///</summary>
		property Magick::Quantum A
		{
			Magick::Quantum get()
			{
				return _Alpha;
			}
			void set(Magick::Quantum value)
			{
				_Alpha = value;
			}
		}
		///==========================================================================================
		///<summary>
		/// Blue component value of this color.
		///</summary>
		property Magick::Quantum B
		{
			Magick::Quantum get()
			{
				return _Blue;
			}
			void set(Magick::Quantum value)
			{
				_Blue = value;
			}
		}
		///==========================================================================================
		///<summary>
		/// Green component value of this color.
		///</summary>
		property Magick::Quantum G
		{
			Magick::Quantum get()
			{
				return _Green;
			}
			void set(Magick::Quantum value)
			{
				_Green = value;
			}
		}
		///==========================================================================================
		///<summary>
		/// Red component value of this color.
		///</summary>
		property Magick::Quantum R
		{
			Magick::Quantum get()
			{
				return _Red;
			}
			void set(Magick::Quantum value)
			{
				_Red = value;
			}
		}
		//===========================================================================================
		static bool operator == (MagickColor^ left, MagickColor^ right)
		{
			return Object::Equals(left, right);
		}
		//===========================================================================================
		static bool operator != (MagickColor^ left, MagickColor^ right)
		{
			return !Object::Equals(left, right);
		}
		//===========================================================================================
		static bool operator > (MagickColor^ left, MagickColor^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return ReferenceEquals(right, nullptr);

			return left->CompareTo(right) == 1;
		}
		//===========================================================================================
		static bool operator < (MagickColor^ left, MagickColor^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return !ReferenceEquals(right, nullptr);

			return left->CompareTo(right) == -1;
		}
		//===========================================================================================
		static bool operator >= (MagickColor^ left, MagickColor^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return ReferenceEquals(right, nullptr);

			return left->CompareTo(right) >= 0;
		}
		//===========================================================================================
		static bool operator <= (MagickColor^ left, MagickColor^ right)
		{
			if (ReferenceEquals(left, nullptr))
				return !ReferenceEquals(right, nullptr);

			return left->CompareTo(right) <= 0;
		}
		//===========================================================================================
		static operator Color (MagickColor^ color)
		{
			if (ReferenceEquals(color, nullptr))
				return Color::Empty;

			return color->ToColor();
		}
		//===========================================================================================
		static operator MagickColor^ (Color color)
		{
			return gcnew MagickColor(color);
		}
		///==========================================================================================
		///<summary>
		/// Compares the current instance with another object of the same type.
		///</summary>
		///<param name="other">The color to compare this color with.</param>
		virtual int CompareTo(MagickColor^ other);
		///==========================================================================================
		///<summary>
		/// Determines whether the specified object is equal to the current color.
		///</summary>
		///<param name="obj">The object to compare this color with.</param>
		virtual bool Equals(Object^ obj) override;
		///==========================================================================================
		///<summary>
		/// Determines whether the specified geometry is equal to the current color.
		///</summary>
		///<param name="other">The color to compare this color with.</param>
		virtual bool Equals(MagickColor^ other);
		///==========================================================================================
		///<summary>
		/// Servers as a hash of this type.
		///</summary>
		virtual int GetHashCode() override;
		///==========================================================================================
		///<summary>
		/// Converts the value of this instance to an equivalent Color.
		///</summary>
		Color ToColor();
		//===========================================================================================
	};
	//==============================================================================================
}