/*++
  Copyright (c) 2011 Microsoft Corporation

  Module Name:

  iz3profiling.h

Abstract:

Some routines for measuring performance.

Author:

Ken McMillan (kenmcmil)

Revision History:

--*/

#ifdef _WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4800)
#pragma warning(disable:4267)
#pragma warning(disable:4101)
#endif

#include "interp/iz3profiling.h"

#include <map>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "util/stopwatch.h"


// FIXME fill in these stubs

#define clock_t double

static  double current_time()
{
  static stopwatch sw;
  static bool started = false;
  if(!started){
    sw.start();
    started = true;
  }
  return sw.get_current_seconds();
}

static void output_time(std::ostream &os, clock_t time){
  os << time;
}


namespace profiling {

  void show_time(){
    output_time(std::cout,current_time());
    std::cout << "\n";
  }

  typedef std::map<const char*, struct node> nmap;

  struct node {
    std::string name;
    clock_t time;
    clock_t start_time;
    nmap sub;
    struct node *parent;

    node();
  } top;

  node::node(){
    time =  0;
    parent = nullptr;
  }

  struct node *current;

  struct init {
    init(){
      top.name = "TOTAL";
      current = &top;
    }
  } initializer;

  struct time_entry {
    clock_t t;
    time_entry(){t = 0;};
    void add(clock_t incr){t += incr;}
  };

  struct ltstr
  {
    bool operator()(const char* s1, const char* s2) const
    {
      return strcmp(s1, s2) < 0;
    }
  };

  typedef  std::map<const char*, time_entry, ltstr> tmap;

  static std::ostream *pfs;

  void print_node(node &top, int indent, tmap &totals){
    for(int i = 0; i < indent; i++) (*pfs) << "  ";
    (*pfs) << top.name;
    int dots = 70 - 2 * indent - top.name.size();
    for(int i = 0; i <dots; i++) (*pfs) << ".";
    output_time(*pfs, top.time);
    (*pfs) << std::endl;
    if(indent != 0)totals[top.name.c_str()].add(top.time);
    for(nmap::iterator it = top.sub.begin(); it != top.sub.end(); it++)
      print_node(it->second,indent+1,totals);
  }

  void print(std::ostream &os) {
    pfs = &os;
    top.time = 0;
    for(nmap::iterator it = top.sub.begin(); it != top.sub.end(); it++)
      top.time += it->second.time;
    tmap totals;
    print_node(top,0,totals);
    (*pfs) << "TOTALS:" << std::endl;
    for(tmap::iterator it = totals.begin(); it != totals.end(); it++){
      (*pfs) << (it->first) << " ";
      output_time(*pfs, it->second.t);
      (*pfs) << std::endl;
    }
  }

  void timer_start(const char *name){
    node &child = current->sub[name];
    if(child.name.empty()){ // a new node
      child.parent = current;
      child.name = name;
    }
    child.start_time = current_time();
    current = &child;
  }

  void timer_stop(const char *name){
    if(current->name != name || !current->parent){
      std::cerr << "imbalanced timer_start and timer_stop";
      exit(1);
    }
    current->time += (current_time() - current->start_time);
    current = current->parent;
  }
}
