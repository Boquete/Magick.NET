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

#include "MagickFormatInfo.h"

using namespace System::Reflection;
using namespace System::Collections::Generic;

namespace ImageMagick
{
	///=============================================================================================
	///<summary>
	/// Class that can be used to initialize Magick.NET.
	///</summary>
	public ref class MagickNET abstract sealed
	{
		//===========================================================================================
	public:
		///==========================================================================================
		///<summary>
		/// Returns the format information of the specified format.
		///</summary>
		static MagickFormatInfo^ GetFormatInformation(MagickFormat format);
		///==========================================================================================
		///<summary>
		/// Adds the sub directory ImageMagick of the current execution path to the environment path.
		/// You should place the supplied ImageMagick dlls in that directory.
		///</summary>
		static void Initialize();
		///==========================================================================================
		///<summary>
		/// Adds the specified path to the environment path. You should place the supplied ImageMagick
		/// dlls in that directory.
		///</summary>
		static void Initialize(String^ path);
		///==========================================================================================
		///<summary>
		/// Pixel cache threshold in megabytes. Once this memory threshold is exceeded, all subsequent
		/// pixels cache operations are to/from disk. This setting is shared by all MagickImage objects.
		///</summary>
		static void SetCacheThreshold(int threshold);
		///==========================================================================================
		///<summary>
		/// Returns information about the supported formats.
		///</summary>
		static property IEnumerable<MagickFormatInfo^>^ SupportedFormats
		{
			IEnumerable<MagickFormatInfo^>^ get()
			{
				return MagickFormatInfo::All;
			}
		}
		///==========================================================================================
		///<summary>
		/// Returns the version of Magick.NET.
		///</summary>
		static property String^ Version
		{
			String^ get()
			{
				Object^ title = (MagickNET::typeid)->Assembly->GetCustomAttributes(AssemblyTitleAttribute::typeid, false)[0];
				Object^ version = (MagickNET::typeid)->Assembly->GetCustomAttributes(AssemblyFileVersionAttribute::typeid, false)[0];
				return ((AssemblyTitleAttribute^)title)->Title + " " + ((AssemblyFileVersionAttribute^)version)->Version;
			}
		}
		//===========================================================================================
	};
	//==============================================================================================
}