#pragma once

#include "db.hpp"
#include "thread.hpp"

#include <memory>
#include <string>

// Fetches the long description for a game from the PlayStation Store (chihiro
// container API).  Runs in its own background thread; main thread polls
// get_status() and reads get_description() only after Status::Found.
class DescriptionFetcher
{
public:
    enum class Status
    {
        Fetching,
        Found,
        NotAvailable,
        Error,
    };

    // Starts the background fetch immediately.
    //
    // The DbItem is only read during construction: the database can be
    // reloaded (TitleDatabase::reload() clears the vector and destroys every
    // item) while this fetch is still in flight, so holding a pointer to it
    // from the worker thread would be a use-after-free.
    DescriptionFetcher(const DbItem* item);
    ~DescriptionFetcher();

    Status            get_status();
    // Safe to call from the main thread at any time; returns empty string
    // until Status::Found.
    std::string       get_description();

private:
    // Immutable snapshot of everything the worker thread needs.  Only written
    // in the constructor, before the thread is started.
    std::string _content;
    std::string _titleid;
    std::string _country;
    std::string _language;

    Mutex       _mutex;
    bool        _abort{false};
    Status      _status{Status::Fetching};
    std::string _description;

    // Created at the very end of the constructor: the worker reads the
    // snapshot fields above immediately, so it must not be running yet when
    // they are still uninitialized.
    std::unique_ptr<Thread> _thread;

    void do_request();
};
