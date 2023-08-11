/*
  Copyright 2023 Northern.tech AS

  This file is part of CFEngine 3 - written and maintained by Northern.tech AS.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  To the extent this program is licensed as part of the Enterprise
  versions of CFEngine, the applicable Commercial Open Source License
  (COSL) may apply to this file if you as a licensee so wish it. See
  included file COSL.txt.
*/

#ifndef CFENGINE_JSON_UTILS_H
#define CFENGINE_JSON_UTILS_H

#include <json.h>

typedef enum {
    DATAFILETYPE_UNKNOWN = 0,
    DATAFILETYPE_JSON,
    DATAFILETYPE_YAML,
    DATAFILETYPE_ENV,
    DATAFILETYPE_CSV
} DataFileType;

void ParseEnvLine(char *raw_line, char **key_out, char **value_out, const char *filename_for_log, int linenumber);
bool JsonParseEnvFile(const char *input_path, size_t size_max, JsonElement **json_out);
bool JsonParseCsvFile(const char *path, size_t size_max, JsonElement **json_out);
JsonElement *JsonReadDataFile(
        const char *log_identifier,
        const char *input_path,
        DataFileType requested_mode,
        size_t size_max);
DataFileType GetDataFileTypeFromString(const char *requested_mode);
DataFileType GetDataFileTypeFromSuffix(const char *filename);
const char *DataFileTypeToString(DataFileType type);

#endif // CFENGINE_JSON_UTILS_H
