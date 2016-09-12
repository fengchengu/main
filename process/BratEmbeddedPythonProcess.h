/*
* This file is part of BRAT 
*
* BRAT is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* BRAT is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#if !defined(_BratProcessWithPython_h_)
#define _BratProcessWithPython_h_

#include "BratProcess.h"

class PythonEngine;


using namespace brathl;
using namespace processes;

namespace processes
{

	class CBratEmbeddedPythonProcess : public CBratProcess
	{
        DECLARE_BASE_TYPE( CBratProcess )

		static const PythonEngine *smPE;

		static bool smPythonStatus;
		static std::string smPythonMessages;

	public:
		// Also loads C++ algorithms
		//
		static bool LoadPythonEngine( const std::string &python_dir );

		static const std::string& PythonMessages()
		{
			return smPythonMessages;
		}


		//instance data

		const std::string mPythonDir;

		//construction / destruction

	public:
		CBratEmbeddedPythonProcess( const std::string &python_dir )
			: base_t()
			, mPythonDir( python_dir )
		{}

		virtual ~CBratEmbeddedPythonProcess()
		{}

		virtual bool Initialize( std::string& msg ) override;
	};

}


#endif		//_BratProcessWithPython_h_
