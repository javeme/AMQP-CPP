/**
 *  Callbacks.h
 *
 *  Class storing deferred callbacks of different type.
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Dependencies
 */
#include <string>
#include <functional>

/**
 *  Set up namespace
 */
namespace AMQP {

/**
 *  Forward declarations
 */
class Message;
class MetaData;

/**
 *  All the callbacks that are supported
 *
 *  When someone registers a callback function for certain events, it should
 *  match one of the following signatures.
 */
#define SuccessCallback      std::function<void()>
#define ErrorCallback        std::function<void(const char *message)>
#define FinalizeCallback     std::function<void()>
#define EmptyCallback        std::function<void()>
#define BeginCallback        std::function<void()>
#define HeaderCallback       std::function<void(const MetaData &metaData)>
#define DataCallback         std::function<void(const char *data, size_t size)>
//#define MessageCallback    std::function<void(Message &&message, uint64_t deliveryTag, bool redelivered)>
#define MessageCallback      std::function<void(const Message &message, uint64_t deliveryTag, bool redelivered)>
#define CompleteCallback     std::function<void(uint64_t deliveryTag, bool redelivered)>
#define QueueCallback        std::function<void(const std::string &name, uint32_t messagecount, uint32_t consumercount)>
#define DeleteCallback       std::function<void(uint32_t deletedmessages)>
#define SizeCallback         std::function<void(uint32_t messagecount)>
#define ConsumeCallback      std::function<void(const std::string &consumer)>
#define CancelCallback       std::function<void(const std::string &consumer)>

/**
 *  End namespace
 */
}
