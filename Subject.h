/*
 * MVC example of GTKmm program
 *
 * Subject class.  Abstract class for Observer Pattern
 *
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include "Observer.h"

// Subject abstract class, part of the Observer pattern
class Subject
{
public:
    // subscribe to events
    void subscribe(Observer*);

    // and unsubscribe
    void unsubscribe(Observer*);

protected:
    // notify changes to all subscribers
    void notify();

private:
    typedef std::set< Observer* > Observers;

    // ordered set of observers
    Observers observers_;
}; // Subject


#endif

