# $Id: Makefile,v 1.113 2003/03/24 23:25:35 jason Exp $

BUILD = ../build
include $(BUILD)/Makefile.pre

PACKAGES += RESIPROCATE  ARES OPENSSL PTHREAD 

CODE_SUBDIRS = os
TARGET_LIBRARY = libresiprocate
TESTPROGRAMS =  

SRC = \
	os/BaseException.cxx \
	os/Coders.cxx \
	os/Condition.cxx \
	os/CountStream.cxx \
	os/Data.cxx \
	os/DataStream.cxx \
	os/Lock.cxx \
	os/Log.cxx \
	os/Logger.cxx \
	os/MD5Stream.cxx \
	os/Mutex.cxx \
	os/ParseBuffer.cxx \
	os/RWMutex.cxx \
	os/Random.cxx \
	os/Socket.cxx \
	os/Subsystem.cxx \
	os/ThreadIf.cxx \
	os/Timer.cxx \
	os/vmd5.cxx \
	SipSession.cxx	\
	Registration.cxx \
	Subscription.cxx \
	DialogSet.cxx \
	Dialog2.cxx \
	XMLCursor.cxx \
	UnknownHeaderType.cxx \
	UnknownParameterType.cxx \
	Embedded.cxx \
	Pidf.cxx \
	MultipartSignedContents.cxx \
	LazyParser.cxx \
	BranchParameter.cxx \
	Connection.cxx \
	ConnectionMap.cxx \
	Contents.cxx \
	DataParameter.cxx \
	Dialog.cxx \
	DnsResolver.cxx \
	Executive.cxx \
	ExistsParameter.cxx \
	FloatParameter.cxx \
	HeaderFieldValue.cxx \
	HeaderFieldValueList.cxx \
	HeaderTypes.cxx \
	Headers.cxx \
	Helper.cxx \
	IntegerParameter.cxx \
	LazyParser.cxx \
	Message.cxx \
	MessageWaitingContents.cxx \
	MethodTypes.cxx \
	MultipartMixedContents.cxx \
	Parameter.cxx \
	ParameterTypes.cxx \
	ParserCategories.cxx \
	ParserCategory.cxx \
	Pkcs7Contents.cxx \
	PlainContents.cxx \
	Preparse.cxx \
	QopParameter.cxx \
	QopParameter.cxx \
	QuotedDataParameter.cxx \
	QuotedDataParameter.cxx \
	RportParameter.cxx \
	SdpContents.cxx \
	Security.cxx \
	SipFrag.cxx \
	ApplicationSip.cxx \
	SipMessage.cxx \
	SipStack.cxx \
	Symbols.cxx \
	TcpTransport.cxx \
	TimerMessage.cxx \
	TimerQueue.cxx \
	TlsTransport.cxx \
	TransactionMap.cxx \
	TransactionState.cxx \
	Transport.cxx \
	TransportSelector.cxx \
	TuIM.cxx \
	UdpTransport.cxx \
	UnknownParameter.cxx \
	Uri.cxx \
	HeaderHash.cxx \
	ParameterHash.cxx \
	MethodHash.cxx 

ifeq ($(HASHES),1)
GPERFOPTS=-D --enum -E -L C++ -t -k '*' --compare-strncmp
GPERFVER="GNU gperf 2.7.2"

%-raw.cxx: %.gperf
	@[ "$$(gperf -v )" == $(GPERFVER) ] || \
		(echo Bogus gperf need:;\
		 echo $(GPERFVER), have: ; gperf -v ; false)
	gperf $(GPERFOPTS) -Z $(*:%-raw=%) $< > $@

# Exceptions (case sensitive)
MethodHash.cxx: MethodHash-raw.cxx
	../util/fixupGperf $< -o $@
	\rm MethodHash-raw.cxx

# The rest of the hashes.
%.cxx: %-raw.cxx
	../util/fixupGperf $< -o $@ --ignorecase
endif

include $(BUILD)/Makefile.post
