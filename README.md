CoffeeEngine
===========

This project is simply a learning tool for DirectX11.  It is a very simplistic 3d engine.

* NOTE: Most of the DirectX11 Direct3d code comes either directly from or as a derivative of the RasterTek samples.

Windows Compilation
-----------

This project requires Windows 7+, DirectX11, and Microsoft Visual Studio 2010.
DirectX11 cannot be developed on a Windows operating system prior to Windows 7.

* Download and install the [DirectX11 SDK] (http://www.microsoft.com/en-us/download/details.aspx?id=6812).

Mac & Linux Compilation
-----------

This is an incomplete section and a pull request for this section would be accepted.

* NOTE: All System classes must be derived from the interface (pure abstract class) 'CoffeeEngine::Interfaces::ISystem.'

OpenGL 
-----------

OpenGL is handled via the [GLEW] (http://glew.sourceforge.net/index.html) libraries.  For Windows development, the GLEW binaries will be enough, but for other OS development, the GLEW libraries must be built.  A link to the GLEW library is provided below.

* GLEW Version 1.10.0

** Windows Development: Download [GLEW] (http://glew.sourceforge.net/index.html) and add the binaries and headers to your repository.
** Linux/Mac Development: Download [GLEW] (http://glew.sourceforge.net/index.html), build the binaries following the instructions on their site, and add the binaries and headers to your repository.

* GLM Version 0.9.5.2: http://glm.g-truc.net/0.9.5/index.html

* NOTE: All Graphics classes must be derived from the (abstract class) 'CoffeeEngine::Graphics::BaseGraphicsClass.'