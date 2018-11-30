/*
* Observer class.  Abstract class for Observer Pattern
*
*
*  Created by Jo Atlee on 06/07/09.
*  Copyright 2009 UW. All rights reserved.
*
*/


#ifndef OBSERVER_H
#define OBSERVER_H

// Observer abstract class, part of the Observer pattern
class Observer {
public:
    virtual ~Observer() {};

    // Triggered updates from notifications from the Subject
	virtual void update() = 0;
};


#endif
