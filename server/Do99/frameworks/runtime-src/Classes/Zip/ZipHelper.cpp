#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ZipHelper.h"
#else
#include "Zip/ZipHelper.h"
#endif

#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip/unzip.h"
#endif

USING_NS_CC;
#define BUFFER_SIZE         8192
#define MAX_FILENAME		512

bool ZipHelper::decompress(const std::string &strZipPath, const std::string& strExtractPath) 
{
	// Find root path for zip file
	size_t pos = strZipPath.find_last_of("/\\");
	if (pos == std::string::npos)
	{
		log("ZipHelper : no root path specified for zip file %s\n", strZipPath.c_str());
		return false;
	}

	// Open the zip file 
	unzFile zipfile = unzOpen(strZipPath.c_str());
	if (!zipfile)
	{
		log("ZipHelper : can not open  zip file %s\n", strZipPath.c_str());
		return false;
	}

	// Get info about the zip file
	unz_global_info global_info;
    
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		log("ZipHelper : can not read file global info of %s\n", strZipPath.c_str());
		unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file 
	char readBuffer[BUFFER_SIZE];
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; i++)
	{
		// Get info about current file
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			log("ZipHelper : can not read compressed file info\n");
			unzClose(zipfile);
			return false;
		}

		const std::string fullPath = strExtractPath + fileName;
		cocos2d::FileUtils * fileUtils = cocos2d::FileUtils::getInstance();

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			// There are not directory entry in some case
			// So we need to create directory when decompressing file entry
			if (!fileUtils->createDirectory(basename(fullPath)))
			{
				log("ZipHelper : can not create directory %s\n", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// Entry is a file, so extract it
			// Open current file
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				log("ZipHelper : can not extract file %s\n", fileName);
				unzClose(zipfile);
				return false;
			}

			// Create a file to store current file 
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (!out)
			{
				log("ZipHelper : can not create decompress destination file %s\n", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}


			// Write current file content to destinate file.
			int error = UNZ_OK;
			do 
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					log("ZipHelper : can not read zip file %s, error code is %d\n", fileName, error);
					fclose(out);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}

			} while (error > 0);

			fclose(out);

		}

		unzCloseCurrentFile(zipfile);


		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				log("ZipHelper : can not read next file for decompressing\n");
				unzClose(zipfile);
				return false;
			}
		}
	}

	unzClose(zipfile);
	return true;
}

bool ZipHelper::decompress(const std::string &zip)
{
	// Find root path for zip file
	size_t pos = zip.find_last_of("/\\");
	if (pos == std::string::npos)
	{
		log("ZipHelper : no root path specified for zip file %s\n", zip.c_str());
		return false;
	}
	const std::string rootPath = zip.substr(0, pos + 1);

	// Open the zip file
	unzFile zipfile = unzOpen(zip.c_str());
	if (!zipfile)
	{
		log("ZipHelper : can not open downloaded zip file %s\n", zip.c_str());
		return false;
	}

	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		log("ZipHelper : can not read file global info of %s\n", zip.c_str());
		unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			log("ZipHelper : can not read compressed file info\n");
			unzClose(zipfile);
			return false;
		}
		const std::string fullPath = rootPath + fileName;
		cocos2d::FileUtils * _fileUtils = cocos2d::FileUtils::getInstance();
		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			//There are not directory entry in some case.
			//So we need to create directory when decompressing file entry
			if (!_fileUtils->createDirectory(basename(fullPath)))
			{
				// Failed to create directory
				CCLOG("ZipHelper : can not create directory %s\n", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// Entry is a file, so extract it.
			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				log("ZipHelper : can not extract file %s\n", fileName);
				unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(fullPath.c_str(), "wb");
			if (!out)
			{
				log("ZipHelper : can not create decompress destination file %s\n", fullPath.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					log("ZipHelper : can not read zip file %s, error code is %d\n", fileName, error);
					fclose(out);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				log("ZipHelper : can not read next file for decompressing\n");
				unzClose(zipfile);
				return false;
			}
		}
	}

	unzClose(zipfile);
	return true;
}

std::string ZipHelper::basename(const std::string& path) 
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(0, found);
	}
	else
	{
		return path;
	}
}
