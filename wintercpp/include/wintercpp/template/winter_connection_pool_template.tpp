//#include <winter_connection_pool_template.h>

namespace winter::templates {

using namespace winter::descriptor;

template <typename TConnection>
ConnectionPool<TConnection>::ConnectionPool(winter::descriptor::PoolDescriptor pool_descriptor) : pool_descriptor_(std::move(pool_descriptor)) {}

template <typename TConnection>
void ConnectionPool<TConnection>::InitPool() {
  if (pool_descriptor_.usePool()) {
#if DEBUG

    std::cout << "*********************************\n";
    std::cout << pool_descriptor_.name() << "\n";
    std::cout << "using pool: " << pool_descriptor_.usePool() << "\n";
    std::cout << "*********************************\n";
#endif
    auto db_pool = [&]() {
      try {
	/// get actual total connections
	size_t actualConnections = available_connections_.size() + in_use_connections_.size();
	/// create the database connections
	if (actualConnections < pool_descriptor_.maxPoolSize()) {
	  /// create or initial poolsize
	  for (unsigned int i = 0; i < pool_descriptor_.initialPoolSize();
	       i++) {
	    AddConn(CreateConn());
	  }
	}
      } catch (const std::runtime_error &e) {
#if DEBUG
	std::cout << "init pool crash \n";
	std::cout << poolDescriptor.name() << "\n";
#endif
	throw WinterException(e.what());
      }
    };
    std::thread db_pool_thread;
    db_pool_thread = std::thread(db_pool);
    db_pool_thread.detach();
  }
}

template <typename TConnection>
void ConnectionPool<TConnection>::CheckConnections() {
  try {
#if DEBUG
    std::cout << "******** CONNECTIONS INFORMATION "
	      << pool_descriptor_.name() << "************* \n";
    std::cout << "free: " << available_connections_.size() << "\n";
    std::cout << "in use: " << in_use_connections_.size() << "\n";
    std::cout
	<< "*************************************************************"
	   "******************* \n";
#endif
    if (available_connections_.empty() && !in_use_connections_.empty()
	&& in_use_connections_.size() < pool_descriptor_.maxPoolSize()) {
#if DEBUG
      std::cout << pool_descriptor_.name()
		<< " NOT AVAILABLE CONNECTIONS Actual connections are less "
		   "than maxPoolSize: "
		<< pool_descriptor_.maxPoolSize()
		<< "creating new connection\n";
#endif
      AddConn(CreateConn());
    } else {
      int intents = 0;
      std::chrono::milliseconds waitTme(500);
      while (available_connections_.empty()) {
#if DEBUG
	std::cout << pool_descriptor_.name()
		  << " NO AVAILABLE CONNECTIONS timeout in seconds is: "
		  << pool_descriptor_.poolTimeout() << " seconds less :"
		  << (pool_descriptor_.poolTimeout() - intents) << " \n";
#endif
	if (intents >= pool_descriptor_.poolTimeout()) {
#if DEBUG
	  std::cout << pool_descriptor_.name()
		    << " timeout end throw exception and releasing "
		       "thread/memory \n";
#endif
	  throw WinterException(
	      "Maximum connection pool size and time reached, no available "
	      "connections!");
	}
	std::this_thread::sleep_for(waitTme);
	intents++;
      }
    }
  } catch (std::runtime_error &e) {
    throw WinterException(e.what());
  }
}

template <typename TConnection>
void ConnectionPool<TConnection>::AddConn(TConnection *conn, bool release) {
  if (release
      || (in_use_connections_.size() + available_connections_.size())
	     < pool_descriptor_.maxPoolSize()) {
    std::scoped_lock lock(pool_mtx_);
    available_connections_.push_back(conn);
  } else {
    delete conn;
    conn = nullptr;
  }
}

template <typename TConnection>
std::shared_ptr<TConnection>
ConnectionPool<TConnection>::Conn() {
  if (pool_descriptor_.usePool()) {
    // CheckConnections need to work without block the thread because if we
    // block the thread all thread waiting will need to wait for the first
    CheckConnections();
    std::scoped_lock lock(pool_mtx_);
    // if not available connections re do this function recursive it will be
    // taken by CheckConnections;
    if (available_connections_.empty()) {
      return Conn();
    }
    in_use_connections_.push_back(available_connections_.front());
    available_connections_.pop_front();
#if DEBUG
    std::cout << pool_descriptor_.name() << " returning connection \n";
#endif
    return std::shared_ptr<TConnection>(
	in_use_connections_.back(),
	std::bind(
	    &ConnectionPool<TConnection>::ReleaseConn,
	    this,
	    std::placeholders::_1));
  } else {
    return std::shared_ptr<TConnection>(CreateConn());
  }
}

template <typename TConnection>
void ConnectionPool<TConnection>::ReleaseConn(TConnection *conn) {
  if (pool_descriptor_.usePool()) {
    // i prefer to create new connection instead of use old connection because
    // if connection get buggy new work will contain old problems the add
    // function block the thread;
    AddConn(CreateConn(), true);

    // block the thread to delete in use connections and delete the old
    // pointer;
    std::scoped_lock lock(pool_mtx_);

    in_use_connections_.erase(
	std::remove_if(
	    in_use_connections_.begin(),
	    in_use_connections_.end(),
	    [&](TConnection *c) {
	      if (c == nullptr) {
		return true;
	      } else if (conn) {
		return c == conn;
	      }
	      return false;
	    }),
	in_use_connections_.end());

    if (conn) {
      delete conn;
      conn = nullptr;
    }
#if DEBUG
    std::cout << "******** RELEASE CONNECTIONS INFORMATION "
	      << pool_descriptor_.name() << "************* \n";
    std::cout << "free: " << available_connections_.size() << "\n";
    std::cout << "in use: " << in_use_connections_.size() << "\n";
    std::cout
	<< "*************************************************************"
	   "******************* \n";
#endif
  }
}

template <typename TConnection>
ConnectionPool<TConnection>::~ConnectionPool() {
  for (auto conn : available_connections_) {
    if (conn) {
      delete conn;
      conn = nullptr;
    }
  }

  for (auto conn : in_use_connections_) {
    if (conn) {
      delete conn;
      conn = nullptr;
    }
  }
}
}  // namespace winter::templates