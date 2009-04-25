#if !defined(RESIP_CONDITION_HXX)
#define RESIP_CONDITION_HXX

#if defined(WIN32)
#  include <windows.h>
#  include <winbase.h>
#else
#  include <pthread.h>
#endif

// !kh!
// Attempt to resolve POSIX behaviour conformance for win32 build.
#define RESIP_CONDITION_WIN32_CONFORMANCE_TO_POSIX

namespace resip
{

class Mutex;

class Condition
{
   public:
      Condition();
      virtual ~Condition();

      void wait (Mutex& mtx);
      /** returns true if the condition was woken up by activity, false if timeout.
       *  or interrupt.
       */
      bool wait (Mutex& mutex, unsigned int ms);
      bool wait (Mutex& mutex, UInt64 start, unsigned int ms);

      // !kh!
      //  deprecate these?
      void wait (Mutex* mutex);
      bool wait (Mutex* mutex, unsigned int ms);

      /** Signal one waiting thread.
       *  Returns 0, if successful, or an errorcode.
       */
      void signal();

      /** Signal all waiting threads.
       *  Returns 0, if successful, or an errorcode.
       */
      void broadcast();

   private:
      // !kh!
      //  no value sematics, therefore private and not implemented.
      Condition (const Condition&);
      Condition& operator= (const Condition&);

   private:
#ifdef WIN32
#  ifdef RESIP_CONDITION_WIN32_CONFORMANCE_TO_POSIX
   // !kh!
   // boost clone with modification
   // credit boost?
   void enterWait ();
   void* m_gate;
   void* m_queue;
   void* m_mutex;
   unsigned m_gone;  // # threads that timed out and never made it to m_queue
   unsigned long m_blocked; // # threads blocked on the condition
   unsigned m_waiting; // # threads no longer waiting for the condition but
                        // still waiting to be removed from m_queue
#  else
   HANDLE mId;
#  endif
#else
   mutable  pthread_cond_t mId;
#endif
};

}

#endif

/* ====================================================================
 * The Vovida Software License, Version 1.0
 *
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * ====================================================================
 *
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
