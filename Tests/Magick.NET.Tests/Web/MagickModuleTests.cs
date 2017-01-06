﻿//=================================================================================================
// Copyright 2013-2017 Dirk Lemstra <https://magick.codeplex.com/>
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

using ImageMagick;
using ImageMagick.Web;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Configuration;
using System.Linq;

namespace Magick.NET.Tests.Web
{
  [TestClass]
  public class MagickModuleTests
  {
    private static MagickModule CreateModule(string config)
    {
      MagickWebSettings settings = TestSectionLoader.Load(config);
      return new MagickModule(settings);
    }

    [TestMethod]
    public void Test_Initialize()
    {
      string config = @"
<magick.net.web canCreateDirectories=""false"" cacheDirectory=""c:\cache"" useOpenCL=""true"">
  <urlResolvers>
    <urlResolver type=""Magick.NET.Tests.TestUrlResolver, Magick.NET.Tests""/>
  </urlResolvers>
</magick.net.web>";

      bool isEnabled = OpenCL.IsEnabled;
      ulong width = ResourceLimits.Width;
      ulong height = ResourceLimits.Height;

      MagickModule module = CreateModule(config);
      module.Initialize();

      Assert.AreEqual(isEnabled, OpenCL.IsEnabled);
      Assert.AreEqual(width, ResourceLimits.Width);
      Assert.AreEqual(height, ResourceLimits.Height);

      config = @"
<magick.net.web canCreateDirectories=""false"" cacheDirectory=""c:\cache"">
  <resourceLimits width=""10000"" height=""20000""/>
  <urlResolvers>
    <urlResolver type=""Magick.NET.Tests.TestUrlResolver, Magick.NET.Tests""/>
  </urlResolvers>
</magick.net.web>";

      module = CreateModule(config);
      module.Initialize();

      Assert.IsFalse(OpenCL.IsEnabled);
      Assert.AreEqual(10000UL, ResourceLimits.Width);
      Assert.AreEqual(20000UL, ResourceLimits.Height);
    }

    [TestMethod]
    public void Test_OnBeginRequest()
    {
      string config = @"
<magick.net.web canCreateDirectories=""false"" cacheDirectory=""c:\cache"" useOpenCL=""true"">
  <urlResolvers>
    <urlResolver type=""Magick.NET.Tests.TestUrlResolver, Magick.NET.Tests""/>
  </urlResolvers>
</magick.net.web>";

      string url = "https://magick.codeplex.com/";

      MagickModule module = CreateModule(config);
      TestHttpContextBase context = new TestHttpContextBase(url);
      module.OnBeginRequest(context);

      Assert.AreEqual(1, context.Items.Count);
      Assert.AreEqual(url, context.Items.Values.Cast<object>().First().ToString());
    }

    [TestMethod]
    public void Test_Exceptions()
    {
      string config = @"<magick.net.web canCreateDirectories=""false"" cacheDirectory=""c:\cache""/>";

      MagickModule module = CreateModule(config);

      ExceptionAssert.Throws<ConfigurationErrorsException>(() =>
      {
        module.Initialize();
      });

      ExceptionAssert.Throws<ConfigurationErrorsException>(() =>
      {
        new MagickModule();
      });
    }
  }
}