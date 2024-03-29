/*++
  Copyright (c) 2012 Microsoft Corporation

  Module Name:

  reg_decl_plugins

Abstract:

Goodie for installing all available declarations
plugins in an ast_manager

Author:

Leonardo de Moura (leonardo) 2012-10-24.

Revision History:

--*/
#ifndef REG_DECL_PLUGINS_H_
#define REG_DECL_PLUGINS_H_

class ast_manager;

void reg_decl_plugins(ast_manager & m);

#endif
