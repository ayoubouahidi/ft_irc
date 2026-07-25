<h2>JOIN Command</h2>

<p>
The <code>JOIN</code> command allows a client to create a new channel or join an
existing one after all channel restrictions have been validated.
</p>

<h3>Creating a New Channel</h3>

<p align="center">
    <img src="images/join-new-channel.png"
         alt="JOIN New Channel Flow"
         width="100%">
</p>

<p align="center">
<b>Figure 1.</b>
Execution flow when joining a channel that does not exist. The server creates
the channel, registers the client as its first member, assigns operator
privileges, and stores the new channel.
</p>

<h3>Joining an Existing Channel</h3>

<p align="center">
    <img src="images/join-existing-channel.png"
         alt="JOIN Existing Channel Flow"
         width="100%">
</p>

<p align="center">
<b>Figure 2.</b>
Execution flow when joining an existing channel. The server validates channel
restrictions such as invite-only mode, password protection, and user limit
before adding the client.
</p>

<hr>

<h2>PRIVMSG Command (Private Message)</h2>

<p>
The <code>PRIVMSG</code> command sends a private message directly to another
connected client.
</p>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/privmsg-private-message.png"
         alt="PRIVMSG to User Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server validates the target nickname. If the user exists, the message is
forwarded; otherwise, <code>401 ERR_NOSUCHNICK</code> is returned.
</p>

<hr>

<h2>PRIVMSG Command (Channel Message)</h2>

<p>
The <code>PRIVMSG</code> command broadcasts a message to all members of a
channel except the sender.
</p>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/privmsg-channel.png"
         alt="PRIVMSG to Channel Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server verifies the channel, checks that the sender belongs to it, and then
broadcasts the message to every other channel member.
</p>

<hr>

<h2>TOPIC Command (Read Topic)</h2>

<p>
The <code>TOPIC</code> command retrieves the current topic of a channel.
</p>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/topic-read-flow.png"
         alt="TOPIC Read Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server validates the channel and membership before returning either the
current topic or indicating that no topic has been set.
</p>

<hr>

<h2>TOPIC Command (Update Topic)</h2>

<p>
The <code>TOPIC</code> command updates the channel topic when the client has the
required permissions.
</p>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/topic-update-flow.png"
         alt="TOPIC Update Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server validates permissions, updates the topic, and broadcasts the new
topic to all channel members.
</p>

<hr>

<h2>INVITE Command</h2>

<p>
The <code>INVITE</code> command allows a client to invite another user into a
channel.
</p>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/invite-command.png"
         alt="INVITE Command Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server validates the sender, target user, and channel before adding the
user to the invitation list and sending the invitation.
</p>

<hr>

<h2>KICK Command</h2>

<p>
The <code>KICK</code> command removes a member from a channel.
</p>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/kick-command-flow.png"
         alt="KICK Command Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server validates permissions, broadcasts the KICK message, removes the
target from the channel, and deletes the channel if it becomes empty.
</p>

<hr>

<h2>MODE Command</h2>

<p>
The <code>MODE</code> command manages channel modes and operator permissions.
</p>

<h3>Supported Modes</h3>

<ul>
    <li><strong>+i / -i</strong> — Invite-only mode.</li>
    <li><strong>+t / -t</strong> — Topic protection.</li>
    <li><strong>+k / -k</strong> — Channel password.</li>
    <li><strong>+l / -l</strong> — User limit.</li>
    <li><strong>+o / -o</strong> — Operator privileges.</li>
</ul>

<h3>Flow Diagram</h3>

<p align="center">
    <img src="images/mode-command-flow.png"
         alt="MODE Command Flow"
         width="100%">
</p>

<p align="center">
<b>Figure.</b>
The server validates permissions, applies the requested channel mode, and
broadcasts the MODE update to every channel member.
</p>

<footer>
    <hr>
    <p>&copy; 2026 FT_IRC 1337 BY HAMZA ELJARY. All rights reserved.</p>
</footer>