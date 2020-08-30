//
// Created by ChanChill on 2020-08-30.
//
//https://leetcode-cn.com/problems/design-twitter/
//example:
//Twitter twitter = new Twitter();
//
//// User 1 posts a new tweet (id = 5).
//twitter.postTweet(1, 5);
//
//// User 1's news feed should return a list with 1 tweet id -> [5].
//twitter.getNewsFeed(1);
//
//// User 1 follows user 2.
//twitter.follow(1, 2);
//
//// User 2 posts a new tweet (id = 6).
//twitter.postTweet(2, 6);
//
//// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
//// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
//twitter.getNewsFeed(1);
//
//// User 1 unfollows user 2.
//twitter.unfollow(1, 2);
//
//// User 1's news feed should return a list with 1 tweet id -> [5],
//// since user 1 is no longer following user 2.
//twitter.getNewsFeed(1);
//
//还有点类中的private 和 friend的设计问题

static int timestamp = 0;

class Tweet{
public:
    int time;
    int id;
    Tweet* next;
    Tweet(int id, int time){
        this->id = id;
        this->time = time;
        this->next = nullptr;
    }
    bool operator<(const Tweet*& t){
        return this->id < t->id;
    }
};


class User{
    int id;

public:
    Tweet* head;
    set<int> followed;
    User(int _id):id(_id), head(nullptr){
        followed.clear();
        follow(id); //关注自己
    }

    void follow(int id){
        followed.insert(id);
    }

    void unfollow(int id){
        if(id != this->id)
            followed.erase(id);
    }

    void post(int tweetId){
        Tweet* tw = new Tweet(tweetId, timestamp);
        timestamp++;
        tw->next = head;
        head = tw;

        // if(head){
        //     cout<<head->id<<endl;
        // }
        // if(head->next){
        //     cout<<head->id<<endl;
        // }
    }
};


class Twitter {
private:
    unordered_map<int, User*> userMap;
public:
    /** Initialize your data structure here. */
    Twitter() {

    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if(userMap.find(userId) == userMap.end()){
            userMap[userId] = new User(userId);
        }
        userMap[userId]->post(tweetId);
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */

    vector<int> getNewsFeed(int userId) {
        vector<int> ans;
        if(userMap.find(userId) == userMap.end()) return ans;
        priority_queue<Tweet*> pq;
        set<int> followed_list = userMap[userId]->followed;

        for(auto i : followed_list){
            Tweet* usr_tw = userMap[i]->head;
            while(usr_tw){
                pq.push(usr_tw);
                usr_tw = usr_tw->next;
            }
        }
        while(!pq.empty()){
            if(ans.size() == 10) break;
            ans.push_back(pq.top()->id);
            pq.pop();
        }
        return ans;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if(userMap.find(followerId) == userMap.end()){
            userMap[followerId] = new User(followerId);
        }
        if(userMap.find(followeeId) == userMap.end()){
            userMap[followeeId] = new User(followeeId);
        }
        userMap[followerId]->follow(followeeId);

    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(userMap.find(followerId) != userMap.end()){
            userMap[followerId]->unfollow(followeeId);
        }
    }
};



/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

